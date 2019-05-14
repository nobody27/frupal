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
}




void Seeker::display() {
    theIsland->displayLocation(location);
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
	//TODO we need a better interface
	int x = getLocation()->xValue + (direction == EAST) - (direction == WEST);
	int y = getLocation()->yValue + (direction == NORTH) - (direction == SOUTH);
  Tile* nextTile = theIsland->getLocation(x,y);
  Obstacle* theObstacle = nextTile->obstacle;
  char choice;	
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
  //theres an obstacle at that tile
	else if (theObstacle != NULL)
  {
    choice = moveObstacle(nextTile); 
  }
  //TODO check you have energy to move here
  if (choice == 'Y' || theObstacle == NULL)
  {
    location = theIsland->getLocation(x,y);
    theIsland->getLocation(x,y)->visitTile();
    energy -= theIsland->getLocation(x,y)->getTerrain()->exertion;
    money += theIsland->getLocation(x,y)->takeMoney();
  }
  return;
}
void Seeker::addTool(Tool* newTool) {
  //deal with special tools
  if(newTool->name == "powerBar") {
	//eat the power bar, get the energy, don't add it to resources
    cout << "Yum! I feel so much stronger now!" << endl;
	energy += newTool->energySaved;
    return;
  } else if(newTool->name == "boat") {
    hasBoat = true;
  } else if (newTool->name == "binoculars") {
    hasBinoculars = true;
  }

  
  //check if tool is already owned, if so +1 that tool
  for(auto it = begin(inventory); it != end(inventory); ++it)
  {
    if(newTool->name == (*it)->name)
    {
      for(auto it2 = begin(gameMgr->theResources->resources); it2 !=
      end(gameMgr->theResources->resources); ++it2)
      {
        if (newTool->name == it2->name)
        {
          it2->quantity++;
          return;
        }
      }
    }
  }

  //else push tool into inventory
  inventory.push_back(newTool);  
}

char Seeker::moveObstacle(Tile* nextTile)
{
    char choice; 
    Tool *relevantTool = NULL;
    Obstacle* theObstacle = nextTile->obstacle;

    //find tool
    for (auto it = begin(gameMgr->theResources->resources); it !=
    end(gameMgr->theResources->resources); ++it)
    {
      if (it->relevantObstacle == theObstacle->name)
      {
        relevantTool = &(*it); 
        break;
      }
    }
    
    //if you've got the tool let them move and tell them they cleared obstacle
    if (relevantTool != NULL)
    {
      //remove the obstacle 
      if (theObstacle->removable)
      {
        nextTile->obstacle = NULL;
      }
      //currently does not still add additional cost on top of moving because we
      //don't check with the user

      //reduce tool count by 1 and/or remove from inventory 
      if (relevantTool->quantity == 1)
      {
        for (auto it = begin(inventory); it != end(inventory); ++it)
        {
          if ((*it) == relevantTool)
          {
            relevantTool->quantity = 0;
            inventory.erase(it);
            break;
          }
        }
      }
      relevantTool->quantity -= 1;
      
      cout << "You used your " << relevantTool->name << " to get past the " 
      << theObstacle->name << "." << endl;
      return 'Y'; 
    }

    //if they don't have the tool ask them
    else
    {
      cout << "You don't have a relevant Tool, would you like waste the extra "
      << theObstacle->energyCost << " energy to get through by hand? ";
      cin >> choice;
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

