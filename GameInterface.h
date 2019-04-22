/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//GameInterFace.h -- header file for the global game I/F

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
using namespace std;

class GameInterface {
public:
	//constructor
	GameInterface();
	//destructor is needed to delete the board seaker, etc.
	~GameInterface();

	//methods for displaying constant printout
	void displayStartupScreen() const;
	void displayExitScreen() const;

	////global data////
	//TODO is there a reason to hide as private and use set/get methods?
	/*
	 * Player Interface handles the interface between what happens 
	 * in the game and instructions from the user.
	 * The main part of this is handling the user menus including:
	 * 	The main menu: switch between configurations, the game, quitting
	 *	The game menu: comands given in the game (perhaps with sub-menus
	 *	The configurations menu: load/save configurations file.
	 *		There may need to be separate files for configurations and game state
	 */
	PlayerInterface* playerIF;

	/*
	 * I think it makes sense to store data structures here, though it is possible
	 * to add another level and store them in some specific class.
	 * Data structures include configurable things like:
	 */

	//	The board: (need to configure the size and terrain)
	Board* theIsland;

	//	The seeker: (need to configure the starting energy, money, etc.)
	Seeker* theSeeker;

	//	Terrain:	a list of known terrain types. each tile in the board will
	// 		point to one of the items in this vector
	vector<Terrain> terrains;

	//	Obstacles: Just like terrain, this will include all possible obstacles
	//		and each tile will point to one of them (or to a null pointer)
	vector<Obstacle> obstacles;

	//	Tools: just like obstacles, but in addition to each tile, the seaker will 
	//		also have a set (or vector, or map) of tools they are carrying
	vector<Tool> tools;

};










#endif // GAME_INTERFACE_H
