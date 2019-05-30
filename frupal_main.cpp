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


	/*
	   srand(time(0));
	//	srand(randomSeed);
	cerr << "seed = " << time(0) <<endl;
	int random = rand(); //TODO erase
	cerr << "random = " << random << endl; //TODO erase
	//clear the screen	
	 */
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
	if(!argv[1]){						//if no argument is provided
		GameManager* gameMgr = new GameManager();	//use default constructor and file
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
	}else{							//if an argument is provided
		GameManager* gameMgr = new GameManager(argv[1]);//pass it to the game manager
		gameMgr->mainMenu->call();	
		////clean up and exit////	
		delete gameMgr;
	}

	return 0;
}
