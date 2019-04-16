#include "Seeker.h"

using namespace std;

Seeker::Seeker()
{
	gold = 10;
	energy = 10;
	x = 0;
	y = 0;
}

void Seeker::display() {
	theIsland.displayLocation(xValue, yValue);
	cout << endl << "You currently have " << energy << " energy and " << gold << " gold pieces." << endl;
}

void Seeker::move(int go) {
	x = theIsland->boardArray[(BOARD_SIZE*x + y) + go]->getX();
	y = theIsland->boardArray[(BOARD_SIZE*x + y) + go]->getY();
}
