/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//GameInterFace.cpp -- implementationof the global game mananger

#include "GameManager.h"
#include "boardNtile.h" 		//owned by Jessica
								//TODO in the future we may want to separate 
								//board and tile to separate files
#include "seeker.h"				//owned by John
//#include "configurations.h"		//owned by Max
//#include "tools.h"				//owned by John (maybe help from Leior)
//#include "obstacles.h"			//TBD (maybe John or Leior)
#include <assert.h>
#include <iostream>
#include "resources.h"

//constructor
GameManager::GameManager() : theIsland(nullptr), theSeeker(nullptr),
theResources(nullptr) ,   initialized(false) 
{
	//TODO configure at least on terrain or arrange for a default terrain
	mainMenu = new MainMenu(this);
	boardOptions = new BoardOptions(this);
  resourcesOptions = new ResourcesOptions(this);
	seekerOptions = new SeekerOptions(this);
}

//destructor
GameManager::~GameManager() {
	delete theIsland;
	delete theSeeker;
	delete mainMenu;
	delete boardOptions;
	delete seekerOptions;
 // delete resourcesOptions;
}

void GameManager::initializeGame() {
	assert(!initialized);
	theIsland = new Board(this, *boardOptions);
  theResources = new Resources(this, *resourcesOptions);
	theSeeker = new Seeker(this, *seekerOptions);
	initialized = true;
	//print introduction
	system("clear");
    cout << endl << endl << "*****************************" << endl;
    cout << "You have landed on Frupal Island!" << endl;
    cout << "As you explore, you will uncover treasure as well as tools to help you on your quest." << endl;
    cout << "Use caution! Moving around the island consumes energy. When you run out of energy, the game will end.";
    cout << endl << "*****************************" << endl;
	cout << "\n\n\n";
	cout << "press ENTER to continue";
	cin.get();
}
