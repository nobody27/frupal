#include "interface.h"

using namespace std;

Interface::Interface() {
	theIsland = NULL;
	character = NULL;
}

int Interface::main_menu() {
	int size = 10;
	char choice = '0';
	cout << endl << endl <<  "Welcome to Frupal Island!" << endl;
	cout << endl << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(P)lay" << "Play game with a randomized map and default character" << endl;
	cout << setw(15) << left <<  "(O)ptions" << "Configure game map and character" << endl;
	cout << setw(15) << left << "(Q)uit" << endl;
    cout << endl << ">";
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
			cout << "Invalid. Please choose from list." << endl;
	}
	return 0;
}

void Interface::game_interface() {
    cout << endl << endl << "*****************************" << endl;
    cout << "You have landed on Frupal Island!" << endl;
    cout << "As you explore, you will uncover treasure as well as tools to help you on your quest." << endl;
    cout << "Use caution! Moving around the island consumes energy. When you run out of energy, the game will end.";
    cout << "*****************************" << endl;

    char choice = '0';
    while (choice != 'Q')
    {
        cout << endl << endl;
        character->display();

        cout << endl << "Please select from the following:" << endl;
        cout << "(N)Go North, (S)Go South, (E)Go East, (W)Go West" << endl;
        cout << "(Q)Quit" << endl;
        cout << endl << ">";

        cin >> choice;
        //TODO check for legal input and capitalize

        int x = character->getLocation()->getX();
        int y = character->getLocation()->getY();
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
            case 'Q':
                return;
            default:
                cout << "Invalid. Please choose from list." << endl;
        }
        if (character->getEnergy() == 0) {
            cout << endl << "You are out of energy!";
            cout << endl << endl << "GAME OVER" << endl << endl;
            return;
        }
    }
}
			
