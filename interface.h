#include "boardNtile.h"
#include "seeker.h"
#include <iostream>
#include <iomanip>

const int BOARD_SIZE = 10;

class Interface
{
	private:
		Board* theIsland;
		Seeker* character;	

	public:	
		int main_menu();
		void game_interface();
};

