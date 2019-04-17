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

//this class contains the necessary methods to interact with the
//human player. Specifically to request commands
class PlayerInterface {
public:
	//method to return the singleton instance of the player interface
	//if necessary create the instance
	static PlayerInterface* instance();
	
	void display();

private:
	//private constructor can only be called from instance() method
	PlayerInterface();
	static PlayerInterface* instance_;
};

//PlayerInterface* getInstance() {return PlayerInterface::instance();}


} //namespace player_interface
#endif // PLAYER_INTERFACE_H
