/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "PlayerInterface.h"
#include "GameMenu.h"
#include "OptionsMenu.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

GameMenu::GameMenu(GameManager* gameManager) : gameMgr(gameManager) quit(false){
	//sub-menu default constructors should be enough
}

//we might be shooting ourselves in the foot implementing a non-essential feature
//but what the heck, why not :)
//done - indicates that we are done with this menu and we should return to the main menu
//quit - indicates that we are performing a quick quit to exit the game immediately
bool GameMenu::call() {
	bool done = false;
	quit = false;

	while (!done && !quit) {
		done = getAndExecuteCommand();
	}
	return quit;
}

void GameMenu::display() const {
	//print the options
	cout << "Welcome to Frupal Island!" << endl;
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play the game. If no options have been configured use a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(O)ptions" << "Configuration options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	//TODO load, save
}

bool GameMenu::getAndExecuteCommand() {
	bool done = false;
	bool again = true;
	
	while(again) {
		again = false;
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input
		switch (toupper(choice)) {
			case 'I':
				gameMgr->theSeeker->move(GameManager::NORTH);
				break;
			case 'J':
				gameMgr->theSeeker->move(GameManager::WEST);
				break;
			case 'K':
				gameMgr->theSeeker->move(GameManager::SOUTH);
				break;
			case 'L':
				gameMgr->theSeeker->move(GameManager::EAST);
				break;
			//TODO buy tool, use tool, view board
			case 'Q':
				done = true;
				break;
			case 'E':
				//exit - quick quit 
				quit = true;
			default:
				cout << "'" << choice << "' is not a valid command in the game menu..." << endl;
				again = true;
		}
	}
	return done;
}
