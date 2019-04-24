/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

//include local files
#include "GameManager.h"
#include "GameMenu.h"
#include "OptionsMenu.h"

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class MainMenu {
public:
	enum state_t {START, QUIT};
	
	//constructor
	MainMenu::MainMenu();
	
	//call and enter the menu
	bool call();	
	//display the command options
	void display() const;
	//execute a main menu command
	void getAndExecuteCommand();

private:
	//the state of the system. currently this tells whether or not it is time to quit
	state_t state;

	//nested menu for playing the game
	//TODO do we need any configuration options for the menu?
	GameMenu gameMenu;

	//nested menu for setting options
	//TODO do we need any configuration options for the menu?
	OptionsMenu optionsMenu;
};

#endif // PLAYER_INTERFACE_H
