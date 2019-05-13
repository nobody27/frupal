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
  Obstacle* theObstacle = theIsland->getLocation(x,y)->obstacle;	
	if (y >= theIsland->size() )
		cout << endl << "You cannot move north!";
	else if (y < 0 )
		cout << endl << "You cannot move south!";
	else if (x >= theIsland->size() )
		cout << endl << "You cannot move east!";
	else if (x < 0 )
		cout << endl << "You cannot move west!";
  //theres an obstacle at that tile
	else if (theObstacle != NULL)
  {
    cout << "There's a " << theObstacle->name << ". ";
    
    for (auto it = begin(inventory); it != end(inventory); ++it, ++i)
    {
      if (it->relevantObstacle == theObstacle->name)
      {
        cout << "Would you like to use your " << it->relevantObstacle << "?" << endl;
      }
      else
      {
        cout << "You don't have a relevant Tool, would you like to try to get "
        << "through the obstacle by hand?" << endl;
      }
    }
  }
  else
	{
		//TODO check you have energy to move here
		location = theIsland->getLocation(x,y);
	    theIsland->getLocation(x,y)->visitTile();
	    energy -= theIsland->getLocation(x,y)->getTerrain()->exertion;
		money += theIsland->getLocation(x,y)->takeMoney();
	}

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
    if(newTool == (*it))
    {
      (*it)->quantity++;
      return;
    }
  }

  //else push tool into inventory
  inventory.push_back(newTool);  
}

/*
bool Seeker::useTool()
{
return false;  //TODO  
}
*/

