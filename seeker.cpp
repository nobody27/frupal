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
  inventory.push_back(&gameManager->theResources->resources.front());
  
  for (auto it = begin(inventory); it != end(inventory); ++it) 
  {
    if ((*it)->name == "BINOCULARS")
    {
      hasBinoculars = true;
    }
  }
}




void Seeker::display() {
    //theIsland->displayLocation(location);
	cout << endl << endl << "You currently have " << energy << " energy and " << money << " gold pieces." << endl;
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
      cout << (*it)->name << setw(5) << right << (*it)->quantity << endl;
    }
  }
}

//TODO check terrain ahead for each call
void Seeker::move(direction_t direction) {
	gameMgr->displayIslandAndSeeker("local");
	//TODO we need a better interface
	int x = getLocation()->xValue + (direction == EAST) - (direction == WEST);
	int y = getLocation()->yValue + (direction == NORTH) - (direction == SOUTH);
    char choice;	
    Tile* nextTile = nullptr; 
    Obstacle* theObstacle = nullptr;
    if (y >= theIsland->size() ) {
		cout << endl << "You cannot move north!";
    return;
    }
	else if (y < 0 ) {
		cout << endl << "You cannot move south!";
    return;
    }
	else if (x >= theIsland->size() ) {
		cout << endl << "You cannot move east!";
    return;
    }
	else if (x < 0 ) {
		cout << endl << "You cannot move west!";
    return;
    }
    nextTile = theIsland->getLocation(x,y);
    theObstacle = nextTile->obstacle;
    if(!hasBoat && nextTile->getTerrain()->getName() == "water") {
		//this is water and you don't have a boat.
		//charge one energy and abort the move
		energy--;
		cout << "\nYou wade through the water but it is too deep." << endl <<
		"You think to yourself... I could really use a boat right now...";
		gameMgr->requestEnter();
		//gameMgr->displayIslandAndSeeker();
		return;
    }
    if (theObstacle) 
    {
    //theres an obstacle at that tile
      choice = moveObstacle(nextTile); 
    }
    //TODO check you have energy to move here
    if (choice == 'Y' || !theObstacle)
    {
      location = theIsland->getLocation(x,y);
      theIsland->getLocation(x,y)->visitTile();
      energy -= theIsland->getLocation(x,y)->getTerrain()->exertion;
      money += theIsland->getLocation(x,y)->takeMoney();
    }
	//gameMgr->requestEnter();
	gameMgr->displayIslandAndSeeker("local");
    return;
} 
void Seeker::addTool(Tool* newTool) {
  //deal with special tools
  if(newTool->name == "POWER BAR") {
	//eat the power bar, get the energy, don't add it to resources
    cout << "Yum! I feel so much stronger now!" << endl;
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
char Seeker::moveObstacle(Tile* nextTile)
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
    
    //if you've got the tool, check if they're down with losing reduced nrg
    if (relevantTool)
    {
      //prompt for ok to lose reduced energy and clear object
      cout << "Use your " << relevantTool->name << " and " << 
      theObstacle->energyCost - relevantTool->energySaved << " additional energy" <<
      " to get past the " << theObstacle->name << "? [Y/N]" << endl;
      
      cin >> choice;
      cin.ignore(100,'\n');
      choice = toupper(choice);
      if (choice == 'Y')
      {
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
      energy -= theObstacle->energyCost - relevantTool->energySaved;
      cout << "You used your " << relevantTool->name << " to get through the "
      << theObstacle->name;
      return choice;
    }
    return 'N';
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
      cout << "You managed to get through the " << theObstacle->name 
      << " with your bare hands!" << endl;
      return choice;
    }
    else
    {
      return 'N';
    }
  }
}

