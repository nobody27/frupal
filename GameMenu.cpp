/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "GameManager.h"
#include "GameMenu.h"
#include "OptionsMenu.h"
#include "seeker.h"
#include "boardNtile.h"

//include libraries
#include <iostream>
#include <iomanip>

using namespace std;

GameMenu::GameMenu(GameManager* gameManager) : gameMgr(gameManager), quit(false){
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
	//system("clear");
	gameMgr->theIsland->displayIsland();
	gameMgr->theSeeker->display();
	//TODO display the board and your locations
    cout << "\n";
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(I) move North" << endl;
	cout << setw(15) << left << "(J) move West" << endl;
	cout << setw(15) << left << "(K) move South" << endl;
	cout << setw(15) << left << "(L) move East" << endl;
    cout << setw(15) << left << "(B)uy an item" << endl;
	cout << setw(15) << left << "(R)eturn to the Main Menu" << endl;
	cout << setw(15) << left << "(Q)uit the program" << endl;
	cout << "\n>";
	//TODO buy tool, use tool
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
/* not needed
        //check for legal input before attempting to capitalize
        while (choice != 'I' && choice != 'i' && choice != 'J' && choice != 'j' && choice != 'K' && choice != 'k' && choice != 'L' && choice != 'l' && choice != 'R' && choice != 'r' && choice != 'Q' && choice != 'q' && choice != 'B' && choice != 'b')
        {
            cout << "\n"; 
            cout << "Invalid input. Please try again." << endl;
            cout << "\n>";
            cin >> choice;
        }
*/
        switch (toupper(choice)) {
            case 'I':
                gameMgr->theSeeker->move(Seeker::NORTH);
                break;
            case 'J':
                gameMgr->theSeeker->move(Seeker::WEST);
                break;
            case 'K':
                gameMgr->theSeeker->move(Seeker::SOUTH);
                break;
            case 'L':
                gameMgr->theSeeker->move(Seeker::EAST);
                break;
                //TODO buy tool, use tool, view board
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
            case 'B':
                shopMenu();        
                break;
            default:
                cout << "'" << choice << "' is not a valid command in the game menu..." << endl;
                again = true;
        }
		if(gameMgr->theSeeker->energy <= 0) {
			gameMgr->theSeeker->display();
            cout << endl << "You are out of energy!";
            cout << endl << endl << "GAME OVER" << endl << endl;
			quit = true;
		}
	}
	return done;
}

bool GameMenu::shopMenu()
{
  string choice;
  cout << "entering shop" << endl;
  gameMgr->theSeeker->displayTools();
  cout << endl << "**Tools for sale**" << endl << endl;
  cout << left << 0 << " " << "Cancel Leave Shop" << endl;
  gameMgr->theResources->displayResources();
  //TODO display tools and available money
  //TODO command to buy an item
  cout << endl << "Money: $" << gameMgr->theSeeker->money << endl << endl;
  cout << "Choice: ";
  cin >> choice;

  //switch statement for purchase
  return true;
}

