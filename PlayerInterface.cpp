/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include locat headers
#include "PlayerInterface.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

namespace player_interface {
PlayerInterface* PlayerInterface::instance_ = nullptr;

PlayerInterface::PlayerInterface() {
	//TODO initialize the singlton
}

PlayerInterface* PlayerInterface::instance() {
	if(!PlayerInterface::instance_) {
		PlayerInterface::instance_ = new PlayerInterface();
	}
	return PlayerInterface::instance_;
}

void PlayerInterface::display() const {
	cout << "Player Interface: " << endl;
	//TODO
}


void PlayerInterface::executeMainMenuCommands() {
	mainMenuCommand_t command = UNDEFINED_MAIN_MENU_COMMAND;
	
	while (command != QUIT) {
		command = getValidMainMenuCommand();
		executeMainMenuCommand(command);
	}
	//quit the game
	return;
}

void PlayerInterface::executeMainMenuCommand(mainMenuCommand_t command) {
	//TODO implement command execution
	switch(command) {
		case QUIT:
			cout << "Thank you for playing." << endl;
			break;
		case PLAY_GAME:
			cout << "get ready to play the game!" << endl;
			//TODO call game command menu
			break;
		default:
			cout << "Sorry, this command has not yet been implemented." << endl;
			cout << "select 'Q' to quit the game" << endl;
	}
}

void PlayerInterface::displayMainMenuCommandOptions() const {
	//print the options
	cout << "Welcome to Frupal Island!" << endl;
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play game with a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(B)oard" << "Configure game board options" << endl;
	cout << setw(15) << left <<  "(S)eeker" << "Configure seeker character options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	//TODO load, save
}

mainMenuCommand_t PlayerInterface::getValidMainMenuCommand() const {
	mainMenuCommand_t command = UNDEFINED_MAIN_MENU_COMMAND;
	
	while(command == UNDEFINED_MAIN_MENU_COMMAND) {
		char choice = 0;
		displayMainMenuCommandOptions();
		//request the command
		cin >> choice;
		command = charToMainMenuCommand(choice);
	}
	return command;
}

mainMenuCommand_t PlayerInterface::charToMainMenuCommand(char choice) const {
	mainMenuCommand_t command;
	//capitalize and check for legal input
	switch (toupper(choice)) {
		case 'P':
			command = PLAY_GAME;
			break;
		case 'B':
			command = CONFIGURE_BOARD;
			break;
		case 'S':
			command = CONFIGURE_SEEKER;
			break;
		case 'Q':
			command = QUIT;
			break;
		default:
			cout << "'" << choice << "' is not a valid command in the main menu..." << endl;
			command = UNDEFINED_MAIN_MENU_COMMAND;
	}
	return command;
}

} //end namespace player_interface
