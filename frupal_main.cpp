/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include libraries
#include <iostream>

//include our files
#include "boardNtile.h"
#include "PlayerInterface.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Hello Frupal" << endl;
	cout << "Fantastic Adventures!" <<endl;
	cout << "team A's adventure game" << endl;
	cout << "This is Elyse's contribution" << endl;
	cout << "This is Max's contribution" << endl;

	Board theIsland;
	//theIsland.display();
	cout << "Here is the island." <<endl;
	theIsland.displayIsland(10);
	theIsland.visitAllTiles();
	theIsland.displayIsland(10);
	
	player_interface::PlayerInterface::instance()->display();
	return 0;
}

