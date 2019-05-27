/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//GameInterFace.h -- header file for the global game manager

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "boardNtile.h" 		//owned by Jessica
								//TODO in the future we may want to separate 
								//board and tile to separate files
#include "seeker.h"				//owned by John
#include "MainMenu.h"			//owned by Elyse
#include "resources.h"
#include <string>


#define RESET "\033[0m"
#define BOLDRED "\033[31;1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define BOLDMAGENTA "\033[1;35m"
#define CYAN "\033[36m"
#define GRAY "\033[90m"
#define LIGHT_GREEN "\033[92m"
#define LIGHT_YELLOW "\033[93m"
#define CYANonBLUE "\033[36;44m"

using namespace std;

//Change this value to enable/disable the screen clearing function
const bool SCREEN_CLEARING_ENABLED = true;

//default config file io parameters
const string DEFAULT_CONFIG_FILE = "defaultConfig.txt";
const string EASY_CONFIG_FILE = "easymode.txt";
const string HARD_CONFIG_FILE = "hardmode.txt";
const string DEFAULT_CONFIG_OUTPUT = "savedConfig.txt";
const char GENERAL_CONFIGURATION = '1';
const char OBSTACLE_CONFIGURATION = '2';
const char TOOL_CONFIGURATION = '3';
const char COMMENT = '#';

//forward declarations of classes used by GameManager
class Board;
class BoardOptions;
class Seeker;
class SeekerOptions;
class MainMenu;
class Resources;
class ResourcesOptions;

class GameManager {
public:
	//constructor
	GameManager();
	//destructor is needed to delete the board seaker, etc.
	~GameManager();

	//initialize everything needed in order to play the game
	//called by main menu before starting the game
	//initialize based on configurations (default if necessary)
	//TODO verify the game is only initialized once unless we implement 

	//function to clear the screen and reset cursor
	void clear_screen() const;

	//Function to obtain and verify a custom file name
	string getFileName();

	//function to read options from the config file
	void readConfigFile(string config);

	//function to write options to config file
	void writeConfigFile();

	//a reset command
	void initializeGame();	

	//display the island and seeker information
	void displayIslandAndSeeker(string command);

	void requestEnter() const;

	////global data////
	//TODO is there a reason to hide as private and use set/get methods?
	/*
	 * MainMenu handles the top level interface with the player
	 * The main part of this is handling the user menus including:
	 * 	The main menu: switch between configurations, the game, quitting
	 *	The game menu: comands given in the game (perhaps with sub-menus
	 *	The configurations menu: load/save configurations file.
	 *		There may need to be separate files for configurations and game state
	 */
	MainMenu* mainMenu; //TODO should this be a pointer or a default field?

	/*
	 * I think it makes sense to store data structures here, though it is possible
	 * to add another level and store them in some specific class.
	 * Data structures include configurable things like:
	 */

	//	The board: (need to configure the size and terrain)
	Board* theIsland;
	BoardOptions* boardOptions;
	//TODO do we need tile options?

	//	The seeker: (need to configure the starting energy, money, etc.)
	Seeker* theSeeker;
	SeekerOptions* seekerOptions;
  
  // The resource repository, need to configure the items at startup
  Resources* theResources;
  ResourcesOptions* resourcesOptions;

	//	Terrain:	a list of known terrain types. each tile in the board will
	// 		point to one of the items in this vector
//TODO	vector<Terrain> terrains;

	//	Obstacles: Just like terrain, this will include all possible obstacles
	//		and each tile will point to one of them (or to a null pointer)
//TODO	vector<Obstacle> obstacles;

	//	Tools: just like obstacles, but in addition to each tile, the seaker will 
	//		also have a set (or vector, or map) of tools they are carrying
//TODO	vector<Tool> tools;
	
	//indicate if we have initialized the game (board, seeker, etc.)
	//init to false
	bool initialized;
	int randomSeed;

	int obstacleDensity = 50;	
	string currentConfig = DEFAULT_CONFIG_FILE;
	
	char NORTHBUTTON = 'I';
	char WESTBUTTON = 'J';
	char SOUTHBUTTON = 'K';
	char EASTBUTTON = 'L';
	char BUYBUTTON = 'B';
	char DISPLAYBUTTON = 'V';
	char QUITBUTTON = 'Q';
	char RETURNBUTTON = 'R';
	char WINBUTTON = 'C';

};

#endif // GAME_INTERFACE_H
