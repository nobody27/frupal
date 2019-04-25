#include "seeker.h"
#include "GameManager.h"
#include "boardNtile.h"

#include <iostream>

using namespace std;

//"default" constructor, only name and relevant obstacle provided
Tool::Tool(string theName, string obstacleName) : energySaved(1) ,
singleUse(true) , price(1) , quantity(1)
{
  name = theName;
  relevantObstacle = obstacleName; 
}

//constructor for when options menu passes in all user selected values for tools
Tool::Tool(string theName, string obstacleName, int theEnergySaved, bool
isSingleUse, int thePrice, int theQuantity) : energySaved(theEnergySaved) ,
singleUse(isSingleUse) , price(thePrice) , quantity(theQuantity)
{
  name = theName;
  relevantObstacle = obstacleName;
}

SeekerOptions::SeekerOptions(GameManager* gameManager) : 
										x(0),
										y(0),
										theEnergy(10),
										theMoney(10),
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
}

//void Seeker::useTool(string relevantObstacle)
//{
 //check if seeker tile obstacle == relevant obstacle 

    //remove obstacle from tile

    //if its single use remove tool from inventory

  //print doesnt work message
  
//  return;
//}


void Seeker::display() {
	//theIsland->displayLocation(location);
	cout << endl << endl << "You currently have " << energy << " energy and " << money << " gold pieces." << endl;
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
	//TODO if energy == 0 GAME OVER
}
void Seeker::addTool(Tool newTool) {
  
  //push tool into inventory
  inventory.push_back(newTool);  

}



