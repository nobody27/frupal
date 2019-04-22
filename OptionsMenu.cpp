/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "OptionsMenu.h"
#include "BoardOptionsMenu.h"
//TODO #include "SeekerOptionsMenu.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

OptionsMenu::OptionsMenu() : state(START) {
	//sub-menu default constructors should be enough
}

bool OptionsMenu::call() {
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

void OptionsMenu::display() const {
	//print the options
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(B)oard size" << endl
	//cout << setw(15) << left << "(S)eeker Options" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	//TODO load, save
}

void OptionsMenu::getAndExecuteCommand() {
	bool commandExecuted = false;
	
	while(!commandExecuted) {
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input
		switch (toupper(choice)) {
			case 'B':
				commandExecuted = setBoardSize();
				break;
			//TODO 
			//case 'S':
			//	commandExecuted = seekerOptionsMenu.call();
			//	break;
			case 'Q':
				state = QUIT;
				commandExecuted = true;
				break;
			default:
				cout << "'" << choice << "' is not a valid command in the options menu..." << endl;
				//commandExecuted remains false
		}
	}
}

bool OptionsMenu::setBoardSize() {
	int size;
	int min = 2;
	int max = 20;
				
	cout << "Please enter Board size [" << min << ".." << max << "]" << endl;
	cin >> size;
	if cin.fail() {
		cout << "ERROR: bad input..." << endl;
		cin.clear();
		return false;
	}
	if(size < min || size > max) {
		cout << "ERROR: out of range." << endl;
		return false;
	}
	
	//success
	gameIF->boardOptions.size = size;
	return true;
}









