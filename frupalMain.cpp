//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//frupalMain.cpp


#include "frupal.h"


int main()
{
	cout << "\nWelcome to Frupal!" <<endl;
	cout << "The A-Team designers are Elyse Max John Leior and Jessica" <<endl;
	cout << "Have an excellent time finding treasure!" <<endl;

	Board theIsland; //object of Board class. Makes default 10X10 island of tiles

	theIsland.display(); //Board display calls each tile display
	
	return 0;
}


