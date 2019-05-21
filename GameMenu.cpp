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
    cout << "\n";
	cout << "Make Your Choice: " << endl;
	cout << setw(15) << left << "(I) move North" << endl;
	cout << setw(15) << left << "(J) move West" << endl;
	cout << setw(15) << left << "(K) move South" << endl;
	cout << setw(15) << left << "(L) move East" << endl;
    cout << setw(15) << left << "(B)uy an item" << endl;
	cout << setw(15) << left << "(D)isplay the seeker's location" << endl;
    //cout << setw(15) << left << "(M) display the full map" << endl; //TODO
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
		cin.ignore(100, '\n');
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
			case 'D':
				gameMgr->displayIslandAndSeeker();
				//gameMgr->clear_screen();
				//gameMgr->theIsland->displayIsland();
				//gameMgr->theSeeker->display();
				break;
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
		else if(gameMgr->theSeeker->location->treasureChar == 'J') {
			cout << GREEN <<  "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
			cout << BLUE << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
			cout << BOLDRED << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
			cout << YELLOW << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
			cout << GREEN << "WELL DONE! You are the greatest treasure seeker ever and you have found the jewel!" <<RESET<<endl;
			quit = true;
			gameMgr->requestEnter();
		}
	}
	return done;
}

bool GameMenu::shopMenu()
{
  int choice = -1;
  vector<Tool>& resources = gameMgr->theResources->resources; //shortcut for convenience
  cout << "entering shop" << endl;
  gameMgr->theSeeker->displayTools();
  cout << endl << "**Tools for sale**" << endl << endl;
  cout << left << 0 << ": " << "Cancel -- Leave Shop" << endl;
  gameMgr->theResources->displayResources();
  //TODO display tools and available money
  //TODO command to buy an item
  cout << endl << "Money: $" << gameMgr->theSeeker->money << endl << endl;
  
  int numRes = static_cast<int>(resources.size());
  
  //make sure its a valid choice and they have enough money
  while(choice < 0 || choice > numRes+1 || 
		(choice != 0 && gameMgr->theSeeker->money <
  resources[choice-1].price) )
  {
    cout << "Enter valid choice you can afford: ";
    cin >> choice;
	if(cin.fail()) {
      cin.clear();
      cin.ignore(100, '\n');
    }
  }

  if(choice == 0)
  {
    return false;
  }

  choice--;

  //subtract the cost from the seekers money
  gameMgr->theSeeker->money -= resources[choice].price;

  //add tool to seeker's inventory
  gameMgr->theSeeker->addTool(&resources[choice]);

  //switch statement for purchase
  return true;
}

