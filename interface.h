#include "boardNtile.h"
#include "Seeker.h"
#include <iostream>

const int BOARD_SIZE = 10;

class Interface
{
	private:
		Board* theIsland;
		Seeker* character;	

	public:	
		void main_menu();
		void game_interface();
}

