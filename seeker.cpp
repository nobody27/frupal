#include "seeker.h"

using namespace std;

Seeker::Seeker(Board* theIsland)
{
	gold = 10;
	energy = 10;
	theIsland = theIsland;
	location = theIsland[0][0]; 
}

void Seeker::display() {
	theIsland.displayLocation(location);
	cout << endl << "You currently have " << energy << " energy and " << money << " gold pieces." << endl;
}

void Seeker::move(int x, int y) {
	if (x => theIsland->getSize())
		cout << "Cannot move to the east";
	else if (y => theIsland->getSize())
		cout << "Cannot move to the north";
	else if (x < 0)
		cout << "Cannot move to the west";
	else if (y < 0)
		cout << "Cannot move to the south";
	else
	{
		location = theIsland->boardArray[x][y];
		energy = energy - 1; //TODO re-implement this based on terrain
	}

}
