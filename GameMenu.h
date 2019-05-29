/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef GAME_MENU_H
#define GAME_MENU_H

//include local files
//#include "GameManager.h"

//forward declarations
class GameManager;

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
//nested menus will be fields nested inside this class
class GameMenu {
public:
	//constructor
	GameMenu(GameManager* gameManager);
	
	//call and enter the menu
	//return true for a quick quit
	bool call();	

private:
	//display the command options
	void display() const;

	//execute a main menu command
	//current implementation is directly in the cpp file
	//TODO consider greating an enum with commands to place in this header file
	//for now try to keep this comment up to date:
	// I - move north
	// J - move west
	// K - move south
	// L - move east
	// R - return to main menu
	// Q - exit (quit quit)

	bool getAndExecuteCommand();
	void shopMenu();
	bool buyTool();
	GameManager* gameMgr;

	//option to quickly quit the game instead of just returning to MainMenu
	bool quit;

};

/*class ShopMenu {
public:
  //constructor
  ShopMenu(GameManager* gameManager);

private:
  //display command options
  void display() const;
  //
*/
#endif // GAME_MENU_H















