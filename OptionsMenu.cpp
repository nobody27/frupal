/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "GameManager.h"
#include "OptionsMenu.h"
#include "seeker.h"
#include "boardNtile.h"

//include libraries
#include <iostream>
#include <iomanip>

#define GRAY "\033[90m"
#define RESET "\033[0m"
using namespace std;

OptionsMenu::OptionsMenu(GameManager* gameManager) : gameMgr(gameManager), quit(false){
	//sub-menu default constructors should be enough
}

//we might be shooting ourselves in the foot implementing a non-essential feature
//but what the heck, why not :)
//done - indicates that we are done with this menu and we should return to the main menu
//quit - indicates that we are performing a quick quit to exit the game immediately
bool OptionsMenu::call() {
	bool done = false;
	quit = false;

	while (!done && !quit) {
		done = getAndExecuteCommand();
	}
	return quit;
}

void OptionsMenu::display() const {
	//print the options
	//system("clear");
	cout << "Make Your Choice: " << endl;
	if(gameMgr->initialized) {
		cout << GRAY;
	}
	//// Place text for options that are not available after initialization here ////
	cout << setw(15) << left << "(S) set board size" << endl;
	cout << setw(15) << left << "(E) set seeker's initial energy level" << endl;
	cout << setw(15) << left << "(M) set seeker's initial money" << endl;
	/////////////////////////////////////////////////////////////////////////////////
	if(gameMgr->initialized) {
		cout << RESET;
	}
	cout << setw(15) << left << "(R)eturn to the Main Menu" << endl;
	cout << setw(15) << left << "(Q)uit the program" << endl;
	cout << "\n\n\n";
	//TODO load, save
}

bool OptionsMenu::getAndExecuteCommand() {
	bool done = false;
	bool again = true;
	bool unsupportedAfterInitialization = false;
	
	while(again) {
		again = false;
		unsupportedAfterInitialization = false;
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input

		//TODO all the code regarding initialized should be moved to methods
		// in order to avoid code duplication
		switch (toupper(choice)) {
			case 'S':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setBoardSize(); //try again if command fails
				}
				break;
			case 'E':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setSeekerEnergy(); //try again if command fails
				}
				break;
			case 'M':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setSeekerMoney(); //try again if command fails
				}
				break;
			//TODO other options
			case 'R':
				cout << "returning to main menu" << endl;
				done = true;
				break;
			case 'Q':
				//exit - quick quit 
				cout << "quitting the game" << endl;
				done = true;
				quit = true;
				break;
			default:
				cout << "'" << choice <<  "' is not a valid command in the game menu..." << endl;
				again = true;
		}
		if(unsupportedAfterInitialization) {
			cout << "'" << choice << "' is not valid after the game has begun..." << endl;
			again = true;
		}
	}
	return done;
}

//TODO create utility method that does the repetative work
bool OptionsMenu::setBoardSize() {
	size_t size = 0;
	cout << "Please enter desired board size" << endl;
	//TODO error handling and check for good range
	cin >> size; cin.ignore(100, '\n');
	if (!size) {
		cout << "invalid size -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->boardOptions->size=size;
	return true; //success
}

bool OptionsMenu::setSeekerEnergy() {
	size_t energy = 0;
	cout << "Please enter how much energy the seeker will start with" << endl;
	//TODO error handling and check for good range
	cin >> energy; cin.ignore(100, '\n');
	if (!energy) {
		cout << "invalid energy -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions->theEnergy=energy;
	return true; //success
}

bool OptionsMenu::setSeekerMoney() {
	size_t money = 0;
	cout << "Please enter how much money the seeker will start with" << endl;
	//TODO error handling and check for good range
	cin >> money; cin.ignore(100, '\n');
	if (!money) {
		cout << "invalid money -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions->theMoney=money;
	return true; //success
}



