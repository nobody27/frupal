/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef MAIN_MENU_H 
#define MAIN_MENU_H

//include local files
//#include "GameManager.h"
#include "GameMenu.h"
#include "OptionsMenu.h"

//include libraries
#include <fstream> //TODO is this needed?

//forward declarations
class GameManager;


//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class MainMenu {
public:
	//constructor
	MainMenu(GameManager* gameManager);
	//when we support an input argument of input/output streams we will need a destructor	
	//call and enter the menu
	bool call();	

private:
	//display the command options
	void display() const;

	//execute a main menu command
	bool getAndExecuteCommand();

	//display a nice exit message
	void displayExitScreen();
	
	//pointer to game manager
	GameManager* gameMgr;

	//nested menu for playing the game
	//TODO do we need any configuration options for the menu?
	GameMenu gameMenu;

	//nested menu for setting options
	//TODO do we need any configuration options for the menu?
	OptionsMenu optionsMenu;

	//string for storing the splash screen text
	string splashText;
};

#endif // MAIN_MENU_H

