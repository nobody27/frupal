#include "seeker.h"
#include "GameManager.h"
#include "boardNtile.h"
#include "resources.h"
#include <iostream>
#include <iomanip>

using namespace std;

SeekerOptions::SeekerOptions(GameManager* gameManager) : 
										x(0),
										y(0),
										theEnergy(20),
										theMoney(20),
										hasBoat(false),
										hasBinoculars(false),
										gameMgr(gameManager)
{
}


//constructor with user input
Seeker::Seeker(GameManager* gameManager, const SeekerOptions& options) :
										location(nullptr),
										energy(options.theEnergy),
										money(options.theMoney),
										inventory(options.theInventory),
										hasBoat(options.hasBoat),
										hasBinoculars(options.hasBinoculars),
										gameMgr(gameManager),
										theIsland(gameManager->theIsland)
{
	location = theIsland->getLocation(options.x, options.y);
    location->visitTile();
//inventory.push_back(&gameManager->theResources->resources.front());
  for (auto it = begin(inventory); it != end(inventory); ++it) 
  {
    if ((*it)->name == "BINOCULARS" && (*it)->quantity > 0)
    {
      hasBinoculars = true;
    }
    else if ((*it)->name == "BOAT" && (*it)->quantity > 0)
    {
      hasBoat = true;
    }
  }
}




void Seeker::display() {
    //theIsland->displayLocation(location);
	cout << "You currently have " << energy << " energy and $" << money;
}

void Seeker::displayTools() {
  cout << endl << endl << "**TOOLS**" << endl;
  if (inventory.empty())
  {
    cout << "You don't have any tools!" << endl;
  }
  else 
  { 
    for (auto it = begin(inventory); it != end(inventory); ++it) 
    {
      cout << (*it)->name << endl;// (*it)->quantity << endl;
    }
  }
}

//TODO check terrain ahead for each call
void Seeker::move(direction_t direction) {
	//gameMgr->displayIslandAndSeeker("local","null");
	//TODO we need a better interface
	int x = getLocation()->xValue + (direction == EAST) - (direction == WEST);
	int y = getLocation()->yValue + (direction == NORTH) - (direction == SOUTH);
    char choice;	
    Tile* nextTile = nullptr; 
    Obstacle* theObstacle = nullptr;
    if (y >= theIsland->size() ) {
		cout << endl << "You cannot move north!" << endl;
    return;
    }
	else if (y < 0 ) {
		cout << endl << "You cannot move south!" << endl;
    return;
    }
	else if (x >= theIsland->size() ) {
		cout << endl << "You cannot move east!" << endl;
    return;
    }
	else if (x < 0 ) {
		cout << endl << "You cannot move west!" << endl;
    return;
    }
    string s;
    nextTile = theIsland->getLocation(x,y);
    theObstacle = nextTile->obstacle;
    if(!hasBoat && nextTile->getTerrain()->getName() == "water") {
		//this is water and you don't have a boat.
		//charge one energy and abort the move
		energy--;
		s = "You wade through the water but it is too deep. \nYou think to yourself... I could really use a boat right now...";
		//gameMgr->requestEnter();
		gameMgr->displayIslandAndSeeker("local", s); //NEW
		return;
    }
    if (theObstacle) 
    //theres an obstacle at that tile
    {
      choice = moveObstacle(nextTile, s);  
    }
    //TODO check you have energy to move here
    if (choice == 'Y' || !theObstacle)
    {
      location = theIsland->getLocation(x,y);
      theIsland->getLocation(x,y)->visitTile();
      energy -= theIsland->getLocation(x,y)->getTerrain()->exertion;
      int m = theIsland->getLocation(x,y)->takeMoney();
      money += m;
      if (m == 0)
          s += "No money here, keep looking";
      else 
      {
          s += "You just found $";
          s += to_string(m);
      }
    }
	//gameMgr->requestEnter();
	gameMgr->displayIslandAndSeeker("local", s);
    return;
} 

void Seeker::addTool(Tool* newTool, string& s) {
  //deal with special tools
  if(newTool->name == "POWER BAR") {
	//eat the power bar, get the energy, don't add it to resources
    s = "Yum! I feel so much stronger now!";
	energy += newTool->energySaved;
	//newTool->quantity--;
    return;
  } else if(newTool->name == "BOAT") {
    hasBoat = true;
  } else if (newTool->name == "BINOCULARS") {
    hasBinoculars = true;
  }

  newTool->quantity++; 
  //check if tool is already owned, if so +1 that tool
  for(auto it = begin(inventory); it != end(inventory); ++it)
  {
    if(newTool == (*it))
    {
      return;
    }
  }

  //else push tool into inventory
  inventory.push_back(newTool);  
}


//TODO need to check there is enough energy
char Seeker::moveObstacle(Tile* nextTile, string& s)
{
    char choice; 
    Tool *relevantTool = NULL;
    Obstacle* theObstacle = nextTile->obstacle;

    //find tool
    for (auto it = begin(inventory); it != end(inventory); ++it)
    {
      if ((*it)->relevantObstacle == theObstacle->name)
      {
        relevantTool = (*it); 
        break;
      }
    }
    
    //if you've got the tool just move
    if (relevantTool)
    {
        //prompt for ok to lose reduced energy and clear object
        //cout << "You used your " << relevantTool->name << " and " << 
        //theObstacle->energyCost - relevantTool->energySaved << " additional energy" <<
        //" to get past the " << theObstacle->name << endl;

        if(relevantTool->singleUse) {
            //reduce tool count by 1 and/or remove from inventory 
            if (relevantTool->quantity == 1)
            {
                for (auto it = begin(inventory); it != end(inventory); ++it)
                {
                    if ((*it) == relevantTool)
                    {
                        inventory.erase(it);
                        break;
                    }
                }
            }
            else {
                relevantTool->quantity -= 1;
            }
        }

        if (theObstacle->removable)
        {
            nextTile->obstacle = NULL;
        }
        s = "You used your " + relevantTool->name + " and " + to_string(theObstacle->energyCost - relevantTool->energySaved) + " additional energy to get past the " + theObstacle->name + "\n\n";
        //cout << "You used your " << relevantTool->name << " to get through the "
        //<< theObstacle->name;
        energy -= theObstacle->energyCost - relevantTool->energySaved;
        return 'Y';
  }
     
  //if they don't have the tool ask them
  else
  {
    cout << "You don't have a relevant Tool to deal with the " << theObstacle->name 
    << ", would you like use the extra "
    << theObstacle->energyCost << " energy to get through by hand? [Y/N]"
    << endl;
    cin >> choice;
    cin.ignore(100,'\n');
    choice = toupper(choice);
    if (choice == 'Y')
    {
      if (theObstacle->removable)
      {
        nextTile->obstacle = NULL;
      }
      energy -= theObstacle->energyCost;
      s = "You managed to get through the " + theObstacle->name + " with your bare hands! \n\n";
      return choice;
    }
    else
    {
      return 'N';
    }
  }
}

