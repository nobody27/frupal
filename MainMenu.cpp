////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "GameManager.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "OptionsMenu.h"

//include libraries
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//TODO add error handling
MainMenu::MainMenu(GameManager* gameManager) : gameMgr(gameManager), 
												gameMenu(gameManager),
												optionsMenu(gameManager)
{
	ifstream splashBuf("splash.txt");
	string tmp;
	while(getline(splashBuf,tmp)) {
		splashText += tmp + "\n";
	}
}

bool MainMenu::call() {
	bool quit = false;
	
	while (!quit) {
		quit = getAndExecuteCommand();
	}
	displayExitScreen();
	return quit;
}

void MainMenu::displayExitScreen() {
	gameMgr->clear_screen();
	cout << BOLDMAGENTA << splashText << RESET << "\n\n";
	cout << "Thank you for playing Frupal Island!" << endl;
	cout << "Please leave a rating in your app store." << endl;
	cout << "\n\n";
}

void MainMenu::display() const {
	//prepare the screen
	gameMgr->clear_screen();
	cout << BOLDMAGENTA << splashText << RESET << "\n\n";
	cout << "Welcome to Frupal Island!" << endl;
    cout << "\n";
	//print the options
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play the game. If no options have been configured use a randomized map and default character" << endl;
	cout << setw(15) << left << "(O)ptions" << "Configuration options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	cout << "\n>";
}

bool MainMenu::getAndExecuteCommand() {
	bool quit = false;
	bool again = true;
	while(again) {
		again = false;
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		cin.ignore(100, '\n');
		switch (toupper(choice)) {
			case 'P':
				//before playing we must make sure everything is initialized
				if(!gameMgr->initialized) {
					gameMgr->initializeGame();
				}
				gameMgr->displayIslandAndSeeker("local", "null");
				quit = gameMenu.call();
				break;
			case 'O':
				quit = optionsMenu.call();
				break;
			case 'Q':
				quit = true;
				break;
			default:
				cout << "'" << choice << "' is not a valid command in the main menu..." << endl;
				again = true;
		}
	}
	return quit;
}
