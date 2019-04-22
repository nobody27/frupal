/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

//include local files
#include "boardOptionsMenu.h"

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class OptionsMenu {
public:
	enum state_t {START, QUIT};
	
	//constructor
	OptionsMenu::OptionsMenu();
	
	//call and enter the menu
	bool call();	
	//display the command options
	void display() const;
	//execute a main menu command
	void getAndExecuteCommand();

private:
	//the state of the system. currently this tells whether or not it is time to quit
	state_t state;

	//nested menu for configuring the board
	BoardOptionsMenu boardOptionsMenu;

	//nested menu for configuring the seeker
	//TODO SeekerOptionsMenu seekerOptionsMenu;

	//TODO configure terrain tools and obstacles separately?
};

#endif //OPTIONS_MENU_H
