#include "interface.h"

using namespace std;

Interface::Interface() {
	theIsland = NULL;
	character = NULL;
}

int Interface::main_menu() {
	int size = 10;
	char choice = '0';
	cout << "Welcome to Frupal Island!" << endl;
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play game with a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(O)ptions" << "Configure game map and character" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
	cin >> choice;
	//TODO capitalize and check for legal input
	
	switch (choice) {
		case 'P':
			theIsland = new Board(size);
			character = new Seeker(theIsland);
			break;
		case 'O':
			break;
		case 'Q':
			return -1;
		default:
			cout << "reached end of switch";
	}
	return 0;
}

void Interface::game_interface() {
	character->display();
	char choice = '0';
	cout << "Please select from the following:" << endl;
	cout << "(N)Go North, (S)Go South, (E)Go East, (W)Go West" << endl;
	cin >> choice;
	//TODO check for legal input and capitalize
	int x = character->getLocation()->getX();
	int y = theIsland->getLocation()->getY();
	while (choice != 'Q') {
		switch (choice) {
			case 'N':
				character->move(x, y+1);
				break;
			case 'S':
				character->move(x, y-1);
				break;
			case 'E':
				character->move(x+1, y);
				break;
			case 'W':
				character->move(x-1, y);
				break;
			default:
				cout << "reached end of switch";
		}
	}
}
			
