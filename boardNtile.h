

//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//boardNtile.h

#ifndef BOARD_N_TILE_H
#define BOARD_N_TILE_H

using namespace std;
#include <iostream>
//#include <cctype>
#include <cstring>
//#include <cstdlib>
#include <string>

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
		string treasure;
		
};


class Board 
{
	public:
		//Board(); //constructor - this default creates a 10x10 board. Calls Board(10)
		Board(int size=10); //constructor - argument from user sizeBoardxsizeBoard
		//destructor is needed because we allocate the array of tiles
		~Board();
		void display() const;
	
	private:
		int boardSize;
		Tile*** boardArray;
};
#endif //BOARD_N_TILE_H
