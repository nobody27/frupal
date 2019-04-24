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
#include <fstream>
#include <iomanip>

using namespace std;

//TODO add error handling
MainMenu::MainMenu() : state(START), splashText("splash.txt") {
}

bool MainMenu::call() {
	bool quit = false;
	state = START;
	
	while (!quit) {
		getAndExecuteCommand();
	}
	displayExitScreen();
	return true;
}

void MainMenu::displayExitScreen() {
	system("clear");
	cout << splashText << "\n\n\n\n\n";
	cout << "Thank you for playing Frupal Island!" << endl;
	cout << "Please leave a rating in your app store. << endl;
}

void MainMenu::display() const {
	//prepare the screen
	system("clear");
	cout << splashText << "\n\n\n\n\n";
	cout << "Welcome to Frupal Island!" << endl;
	//print the options
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play the game. If no options have been configured use a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(O)ptions" << "Configuration options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	cout << "\n\n\";
}

bool MainMenu::getAndExecuteCommand() {
	bool quit = false;
	bool done = false;
	while(!done) {
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input
		switch (toupper(choice)) {
			case 'P':
				//before playing we must make sure everything is initialized
				if(!gameMgr->initialized) {
					gameMgr->initialize();
				}
				quit = gameMenu.call();
				break;
			case 'O':
				quit = optionsMenu.call();
				break;
			case 'Q':
				done = true;
				quit = true;
				break;
			default:
				cout << "'" << choice << "' is not a valid command in the main menu..." << endl;
				//done remains false
		}
	}
	return quit;
}
