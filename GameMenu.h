/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef GAME_MENU_H
#define GAME_MENU_H

//include local files
#include "GameManager.h"

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class GameMenu {
public:
	//constructor
	GameMenu::GameMenu();
	
	//call and enter the menu
	bool call();	

private:
	//display the command options
	void display() const;

	//execute a main menu command
	void getAndExecuteCommand();

	//nested menu for playing the game
	//TODO do we need any configuration options for the menu?

	//nested menu for setting options
	//TODO do we need any configuration options for the menu?
};

#endif // PLAYER_INTERFACE_H
