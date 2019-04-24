/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//GameInterFace.cpp -- implementationof the global game mananger

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "boardNtile.h" 		//owned by Jessica
								//TODO in the future we may want to separate 
								//board and tile to separate files
#include "seeker.h"				//owned by John
#include "PlayerInterface.h"	//owned by Elyse
#include "configurations.h"		//owned by Max
#include "tools.h"				//owned by John (maybe help from Leior)
#include "obstacles.h"			//TBD (maybe John or Leior)

#include <assert.h>
#include <iostream>

//constructor
GameManager::GameManager() : MainMenu(this), 
							theIsland(nullptr), 
							boardOptions(this),
							theSeeker(nullptr), 
							seekerOptions(this),
							initialized(false) {
	//TODO configure at least on terrain or arrange for a default terrain
}

//destructor
GameManager::~GameManager() {
	delete theIsland;
	delete theSeeker;
}

GameManager::initializeGame() {
	assert(!initialized);
	theIsland = new Board(this, boardOptions);
	theSeeker = new Seeker(this, seekerOptions);
	initialized = true;
	//print introduction
	system("clear");
    cout << endl << endl << "*****************************" << endl;
    cout << "You have landed on Frupal Island!" << endl;
    cout << "As you explore, you will uncover treasure as well as tools to help you on your quest." << endl;
    cout << "Use caution! Moving around the island consumes energy. When you run out of energy, the game will end.";
    cout << endl << "*****************************" << endl;
	cout << "\n\n\n";
	cout << "press ENTER to continue"";
	cin.get();
}
