/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

//include local files
//#include "GameManager.h"

//forward declarations
class GameManager;


//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class OptionsMenu {
public:
	//constructor
	OptionsMenu(GameManager* gameManager);

	//call and enter the menu
	//return true for a quick quit
	bool call();	

private:
	//display the command options
	void display() const;

	//execute a main menu command
	//current implementation is directly in the cpp file
	//TODO consider greating an enum with commands to place in this header file
	//for now try to keep this comment up to date:
	// S - set board size
	// E - set seeker's initial energy level
	// M - set seeker's initial money (gold) level
	// R - return to main menu
	// Q - exit (quick quit)
	bool getAndExecuteCommand();

	//read size_t arg and set the size
	//TODO range enforsement and error handling
	bool setBoardSize();

	//read size_t arg and set the energy
	//TODO range enforsement and error handling
	bool setSeekerEnergy();

	//read size_t arg and set the money
	//TODO range enforsement and error handling
	bool setSeekerMoney();

	//read in a specific random seed to recreate a specific game
	//TODO allow this to be red from the config file
	bool setRandomSeed();

	void configureGeneralSettings();

	void configureTools();
	void addTool();
	void removeTool();
	void modifyTool(int toolNumber);

	void configureObstacles();
	void addObstacle();
	void removeObstacle();
	void modifyObstacle(int obstacleNumber);

	GameManager* gameMgr;

	//option to quickly quit the game instead of just returning to MainMenu
	bool quit;

};

#endif // OPTIONS_MENU_H
