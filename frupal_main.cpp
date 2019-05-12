/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include libraries
#include <iostream>

//include our files
#include "GameManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	//clear the screen	
	system("clear");

	////initialize the game interface////
	/* 
	 * this will be a kind of "god view" of the system that includes
	 * pointers to: 
	 * 	player_interface:	print output and collect input from the human players
	 * 	configurations:		store all configurable data including lists of tools, 
							obstacle, serrain types, board size, etc.
	 *	board:				The island of frupal, a matrix of locations with tiles 
	 *	seeker: 			our hero/heroine
	 */
	GameManager* gameMgr = new GameManager();

	////call the main menu////
	/* 
	 * this is where everything happens.
	 * I envision some kind of startup message like the flash screen Max prepared
	 * then call the main menu to set up configurations etc.
	 *
	 * if the player chooses to start playing without setting configurations
	 * we need to construct everything with a default constructor (or default configurations)
	 *
	 * note: before quitting we should ask the player if they want to save the configurations
	 * 		and/or save the game (if the game is not over)
	 */
	gameMgr->mainMenu->call();	

	////clean up and exit////	
	delete gameMgr;
	return 0;
}

