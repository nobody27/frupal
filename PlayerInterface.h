/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

//include libraries
#include <iostream>

using namespace std;

//create a namespace in which to compartmentalize the "global"
//pointer to the singleton instance of the player interface
namespace player_interface {

//commands from the main menue
//TODO should configuring terrain, tools, obstacles, etc. be part of the board 
//or their own sections?
enum mainMenuCommand_t {UNDEFINED_MAIN_MENU_COMMAND,
						CONFIGURE_BOARD, 
						CONFIGURE_SEEKER, 
						LOAD_GAME, 
						PLAY_GAME,
						SAVE_GAME, 
						QUIT};

//commands for playing the game
enum gameCommand_t {UNDEFINED_GAME_COMMAND,
					LOOK, 
					MOVE, 
					BUY_TOOL, 
					USE_TOOL, 
					RETURN_TO_MAIN_MENU};

enum direction_t {NORTH, SOUTH, EAST, WEST};

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
class PlayerInterface {
public:
	//method to return the singleton instance of the player interface
	//if necessary create the instance
	static PlayerInterface* instance();
	
	//print options and ask player for main menu commands
	//until player decides to quit the game
	void executeMainMenuCommands();	

	//execute a single main menu command and return to main menu
	void executeMainMenuCommand(mainMenuCommand_t command);	

	//display main menu command options to user
	void displayMainMenuCommandOptions() const;

	//get user input for which main menu command to run
	mainMenuCommand_t getValidMainMenuCommand() const;

	//convert char input to command type
	mainMenuCommand_t charToMainMenuCommand(char choice) const;

	//display text introuding the player to the game
	void displayGameIntroduction() const;

	//execute commands in the game until the player requests
	//to return to the main menu
	void executeGameCommands();

	//get desired direction from player for relevant command
	//i.e. move or look command
	//TODO - should we only list possible directions?
	//TODO -void selectDirection() const;

	//get desired tool from the player for relevant command
	//i.e. buy or use command
	//select from tools belonging to the seeker
	//TODO - void selectTool() const;
	
	void display() const;

private:
	//private constructor can only be called from instance() method
	PlayerInterface();
	static PlayerInterface* instance_;
	//store whether pr not we need to display the game introduction
	//before moving to the game menu
	bool displayGameIntro;
};

//PlayerInterface* getInstance() {return PlayerInterface::instance();}


} //namespace player_interface
#endif // PLAYER_INTERFACE_H
