/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "PlayerInterface.h"
#include "OptionsMenu.h"
#include "OptionsMenu.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

OptionsMenu::OptionsMenu(GameManager* gameManager) : gameMgr(gameManager) quit(false){
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
	system("clear");
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(S) set board size" << endl;
	cout << setw(15) << left << "(E) set seeker's initial energy level" << endl;
	cout << setw(15) << left << "(M) set seeker's initial money" << endl;
	cout << setw(15) << left << "(R)eturn to the Main Menu" << endl;
	cout << setw(15) << left << "(Q)uit the program" << endl;
	cout << "\n\n\n";
	//TODO load, save
}

bool OptionsMenu::getAndExecuteCommand() {
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
			case 'S':
				again = !setBoardSize(); //try again if command fails
				break;
			case 'E':
				again = !setSeekerEnergy(); //try again if command fails
				break;
			case 'M':
				again = !setSeekerMoney(); //try again if command fails
				break;
			//TODO other options
			case 'R':
				done = true;
				break;
			case 'Q':
				//exit - quick quit 
				quit = true;
			default:
				cout << "'" << choice << "' is not a valid command in the game menu..." << endl;
				again = true;
		}
	}
	return done;
}

//TODO create utility method that does the repetative work
bool OptionsMenu::setBoardSize() {
	size_t size;
	cout << "Please enter desired board size" << endl;
	//TODO error handling and check for good range
	if (!cin >> size) {
		cout << "invalid size -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->boardOptions.size=size;
	return true; //success
}

bool OptionsMenu::setSeekerEnergy) {
	size_t energy;
	cout << "Please enter how much energy the seeker will start with" << endl;
	//TODO error handling and check for good range
	if (!cin >> energy) {
		cout << "invalid energy -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions.energy=energy;
	return true; //success
}

bool OptionsMenu::setSeekerMoney) {
	size_t money;
	cout << "Please enter how much money the seeker will start with" << endl;
	//TODO error handling and check for good range
	if (!cin >> money) {
		cout << "invalid energy -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions.money=money;
	return true; //success
}



