/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include locat headers
#include "PlayerInterface.h"

//include libraries
#include <iostream>

using namespace std;

namespace player_interface {
PlayerInterface* PlayerInterface::instance_ = nullptr;

PlayerInterface::PlayerInterface() {
	//TODO initialize the singlton
}

PlayerInterface* PlayerInterface::instance() {
	if(!PlayerInterface::instance_) {
		PlayerInterface::instance_ = new PlayerInterface();
	}
	return PlayerInterface::instance_;
}

void PlayerInterface::display() {
	cout << "Player Interface: " << endl;
	//TODO
}


} //end namespace player_interface
