/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "MainMenu.h"
#include "GameMenu.h"
#include "OptionsMenu.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

MainMenu::MainMenu() : state(START) {
	//sub-menu default constructors should be enough
}

bool MainMenu::call() {
	bool retVal = false;
	state = START;
	
	while (state != QUIT) {
		getAndExecuteCommand();
	}
	//exit game -- TODO if not saved, ask to save first
	if(state == QUIT) {
		//TODO - is there any other option?
		retVal = true;
	}
	return retVal;
}

void MainMenu::display() const {
	//print the options
	cout << "Welcome to Frupal Island!" << endl;
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play the game. If no options have been configured use a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(O)ptions" << "Configuration options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	//TODO load, save
}

void MainMenu::getAndExecuteCommand() {
	bool commandExecuted = false;
	
	while(!commandExecuted) {
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input
		switch (toupper(choice)) {
			case 'P':
				//before playing we must make sure everything is initialized
				if(!gameIF->initialized) {
					gameIF->initialize();
				}
				commandExecuted = gameMenu.call();
				break;
			case 'O':
				commandExecuted = optionsMenu.call();
				break;
			case 'Q':
				state = QUIT;
				commandExecuted = true;
				break;
			default:
				cout << "'" << choice << "' is not a valid command in the main menu..." << endl;
				//commandExecuted remains false
		}
	}
}
