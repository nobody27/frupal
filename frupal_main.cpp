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
#include "Seeker.h"
#include "interface.h"

extern const int BOARD_SIZE = 10;

using namespace std;

int main(int argc, char* argv[]) {
	Interface interface;
	int i = interface.main_menu();
	if (i == -1)
		return 0;
	interface.game_interface();
	return 0;
}

