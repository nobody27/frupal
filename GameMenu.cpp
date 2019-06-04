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
#include "colors.h"

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
	//line 1


    cout << endl << "***************************************" << endl;
	cout << "\n";
	cout << GAME_MENU_COLOR << "Make Your Choice: " << endl;
	cout << setw(15) << right << "(" << gameMgr->NORTHBUTTON << ") move North";
	cout << setw(18) << left << " ";
	cout << "(" << gameMgr->BUYBUTTON << ") Buy an item";
	cout << setw(8) << " ";
	cout << "(" << gameMgr->DISPLAYBUTTON << ") View seeker's location";
	cout << setw(3) << " ";
    cout << "(" << gameMgr->DISPLAYFULLBUTTON << ") View full island" << endl;

	//line 2
	cout << "(" << gameMgr->WESTBUTTON << ") move West";
	cout << "               ";
	cout << " (" << gameMgr->EASTBUTTON << ") move East";
	cout << setw(4) << " ";
	cout << GAME_MENU_COLOR << "(" << gameMgr->QUITBUTTON << ") Quit the program";
	cout << "   (" << gameMgr->RETURNBUTTON << ") Return to Menu";
	cout << "           (" << gameMgr->WINBUTTON << ") Cheat!" << endl; //TODO

    //line 3
	cout << "              (" << gameMgr->SOUTHBUTTON << ") move South" << endl;
	cout << ">";
	//cout << RESET;

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
		choice = toupper(choice);
		switch (choice) {
				//TODO buy tool, use tool, view board
			case 'V':
				gameMgr->displayIslandAndSeeker("local", "null");
				//gameMgr->clear_screen();
				//gameMgr->theIsland->displayIsland();
				//gameMgr->theSeeker->display();
				break;
			case 'M':
				gameMgr->displayIslandAndSeeker("full", "null");
				break;
			case 'C':
				gameMgr->theSeeker->location = gameMgr->theIsland->jewelTile; 
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
				if(choice == gameMgr->NORTHBUTTON){
					gameMgr->theSeeker->move(Seeker::NORTH);
				}else if(choice == gameMgr->WESTBUTTON){
					gameMgr->theSeeker->move(Seeker::WEST);
				}else if(choice == gameMgr->SOUTHBUTTON){
					gameMgr->theSeeker->move(Seeker::SOUTH);
				}else if(choice == gameMgr->EASTBUTTON){
					gameMgr->theSeeker->move(Seeker::EAST);
				}else{
					//gameMgr->displayIslandAndSeeker("local", "null");
					cout << endl << "'" << choice << "' is not a valid command in the game menu..." << endl;
					again = true;
				}
		}
		if(gameMgr->theSeeker->energy <= 0) {
			gameMgr->displayIslandAndSeeker("endgame", "null");
			cout << endl << "You are out of energy!";
			cout << endl << endl << "GAME OVER" << endl << endl;
			gameMgr->requestEnter();
			quit = true;
		}
		else if(gameMgr->theSeeker->location == gameMgr->theIsland->jewelTile) {
			gameMgr->displayIslandAndSeeker("endgame", "null");
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

void GameMenu::shopMenu()
{
	//do
	//{
	//	gameMgr->displayIslandAndSeeker("local", "null");
	//}
    string s;
	while(buyTool(s)) {}
	gameMgr->displayIslandAndSeeker("local", s);
}

bool GameMenu::buyTool(string& s)
{
	int choice = -1;
	vector<Tool>& resources = gameMgr->theResources->resources; //shortcut for convenience
	cout << "entering shop" << endl;
	gameMgr->theSeeker->displayTools();
	cout << endl << "**Tools for sale**" << endl << endl;
	gameMgr->theResources->displayResources();
	cout << endl << left << 0 << " " << "**EXIT SHOP**" << endl;
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
      return false;
		}
	}

	if(choice == 0)
	{
		return false;
	}

	choice--;
 
  //check the tool isn't permanent and don't buy if they have it
   
  
  for(auto it = begin(gameMgr->theSeeker->inventory); it !=
  end(gameMgr->theSeeker->inventory); ++it)
  {
    if(resources[choice].name == (*it)->name && !resources[choice].singleUse)
    {
      cout << "you already have this multi-use tool!" << endl; 
      return true;
    }
  }


	//subtract the cost from the seekers money
	gameMgr->theSeeker->money -= resources[choice].price;

	//add tool to seeker's inventory
	gameMgr->theSeeker->addTool(&resources[choice], s);

	//switch statement for purchase
	return true;
}

