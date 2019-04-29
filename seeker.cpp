#include "seeker.h"
#include "GameManager.h"
#include "boardNtile.h"
#include "resources.h"
#include <iostream>

using namespace std;

SeekerOptions::SeekerOptions(GameManager* gameManager) : 
										x(0),
										y(0),
										theEnergy(20),
										theMoney(20),
										gameMgr(gameManager)
{
}


//constructor with user input
Seeker::Seeker(GameManager* gameManager, const SeekerOptions& options) :
												location(nullptr),
												energy(options.theEnergy),
												money(options.theMoney),
												inventory(options.theInventory),
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
      cout << (*it)->name << endl;
    }
  }
}

//TODO check terrain ahead for each call
void Seeker::move(direction_t direction) {
	//TODO we need a better interface
	int x = getLocation()->xValue + (direction == EAST) - (direction == WEST);
	int y = getLocation()->yValue + (direction == NORTH) - (direction == SOUTH);
	
	if (y >= theIsland->size() )
		cout << endl << "You cannot move north!";
	else if (y < 0 )
		cout << endl << "You cannot move south!";
	else if (x >= theIsland->size() )
		cout << endl << "You cannot move east!";
	else if (x < 0 )
		cout << endl << "You cannot move west!";
	else
	{
		location = theIsland->getLocation(x,y);
    
    theIsland->getLocation(x,y)->visitTile();
		
    energy = energy - 1; //TODO re-implement this based on terrain
	}

}
void Seeker::addTool(Tool* newTool) {
  
  //push tool into inventory
  inventory.push_back(newTool);  
}


