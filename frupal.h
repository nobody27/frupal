

//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//frupal.h


using namespace std;
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

class Tile
{
	public:
		Tile(int xValue, int yValue); //constructor
		//~Tile();
		void tileDisplay();

	private:
		int xValue;
		int yValue;
		int terrain;
		int treasure;
};


class Board 
{
	public:
		//Board(); //constructor - this default creates a 10x10 board. Calls Board(10)
		Board(int size=10); //constructor - argument from user sizeBoardxsizeBoard
		//~Board();
		void display();
	
	private:
		int boardSize;
		Tile***boardArray;
};
