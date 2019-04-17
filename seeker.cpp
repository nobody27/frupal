#include "seeker.h"

using namespace std;

Seeker::Seeker(Board* theIsland)
{
	money = 10;
	energy = 10;
	this->theIsland = theIsland;
	location = theIsland->getLocation(0,0);
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

}
