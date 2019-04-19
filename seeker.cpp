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

//default constructor
Seeker::Seeker() : energy(10) , money(10)
{
  this->theIsland = theIsland;
  location = theIsland->getLocation(0,0);
}

//constructor with user input
Seeker::Seeker(Tile* theLocation, int theEnergy, int theMoney, vector<Tool>
theInventory) : energy(theEnergy) , money(theMoney) , inventory(theInventory)
{
	this->theIsland = theIsland;
	location = theLocation;
}

void apply(string relevantObstacle)
{
  return;
}

void Seeker::display() {
	theIsland->displayLocation(location);
	cout << endl << endl << "You currently have " << energy << " energy and " << money << " gold pieces." << endl;
}

void Seeker::move(int x, int y) {
	if (x >= theIsland->getSize())
		cout << endl << "You cannot move east!";
	else if (y >= theIsland->getSize())
		cout << endl << "You cannot move north!";
	else if (x < 0)
		cout << endl << "You cannot move west!";
	else if (y < 0)
		cout << endl << "You cannot move south!";
	else
	{
		location = theIsland->getLocation(x,y);
		energy = energy - 1; //TODO re-implement this based on terrain
	}

void Seeker::useTool() {

}
