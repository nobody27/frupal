#include <string>
#include "seeker.h"

using namespace std;

//"default" constructor, only name and relevant obstacle provided
Tool::Tool(string theName, string obstacleName) : energySaved(1) ,
singleUse(TRUE) , price(1) , quantity(1)
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
										gameMgr(gameManager),
										theLocation(gameManager->theIsland[0][0]),
										theEnergy(10),
										theMoney(10)
{
}


//constructor with user input
Seeker(GameManager* gameManager, const SeekerOptions& options) :
												location(options.theLocation),
												energy(options.energy),
												money(options.money),
												inventory(options.theInventory),)
												gameMgr(GameManager),
												theIsland(GameManager->theIsland)
{
}

void Seeker::applyTool(string relevantObstacle)
{
 //check if seeker tile obstacle == relevant obstacle 

    //remove obstacle from tile

    //if its single use remove tool from inventory

  //print doesnt work message
  
  return;
}


void Seeker::display() {
	//theIsland->displayLocation(location);
	cout << endl << endl << "You currently have " << energy << " energy and " << money << " gold pieces." << endl;
}

//TODO check terrain ahead for each call
void Seeker::move(GameManager::direction_t direction) {
	//TODO we need a better interface
	int x = theLocation->xValue + (direction == GameManager::EAST) - (direction == GameManager::WEST);
	int y = theLocation->yValue + (direction == GameManager::NORTH) - (direction == GameManager::SOUTH);
	
	if (y >= theIsland->getSize() )
		cout << endl << "You cannot move north!";
	else if (y < 0 )
		cout << endl << "You cannot move south!";
	else if (x >= theIsland->getSize() )
		cout << endl << "You cannot move east!";
	else if (x < 0 )
		cout << endl << "You cannot move west!";
	else
	{
		location = theIsland->setLocation(x,y);
		energy = energy - 1; //TODO re-implement this based on terrain
	}
	//TODO if energy == 0 GAME OVER
}
void Seeker::addTool(Tool newTool) {
  
  //push tool into inventory
  inventory.push_back(newTool);  

}
void Seeker::useTool() {

}




