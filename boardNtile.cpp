//
//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//frupalMain.cpp

//constructors destructors and functions of Board and Tile classes

#include "boardNtile.h"

using namespace std;

Tile::Tile(int x, int y)
{
	xValue=x;
	yValue=y;
	terrain=0; //grassy meadow (later enum)
	treasure=("Nothing here! Better luck next time."); //no treasure - later string with description
}

void Tile::tileDisplay()
{
	cout << "	Position: (" << xValue << "," <<
				yValue << ")" << endl;
	cout << "	Terrain: " << terrain<<endl;
	cout << "	Treasure: " << treasure<<endl;
}



/*
Board::Board()
{
				Board(10);
}
*/

Board::Board(int size)
{
	boardSize = size;
	boardArray = new Tile**[size];	
	for(int i=0; i<size; ++i)
	{
		boardArray[i]= new Tile*[size];
		for(int j=0; j<size; ++j)
		{
			boardArray[i][j]=new Tile(i,j);
		}
	}
}

Board::~Board()
{
	delete[] boardArray;
}

void Board::displayIsland() const
{
	cout << "Displaying your island: " <<endl;
	for(int i=0; i<boardSize; ++i)
	{
		for(int j=0; j<boardSize; ++j)
		{
			cout <<"the Tile at (" << i << ", " << j <<") has  data" <<endl;
			boardArray[i][j]->tileDisplay();
		}
		cout <<endl;
	}
}

void Board::displayLocation(int x, int y) const
{
	boardArray[y][x]->displayLocation();
	cout << endl << "To the north is a ";
	boardArray[(BOARD_SIZE*x + y) - BOARD_SIZE]->getTerrain();
	cout << endl << "To the south is a ";
	boardArray[(BOARD_SIZE*x + y) + BOARD_SIZE]-getTerrain();
	cout << endl << "To the east is a ";
	boardArray[y][x+1]->getTerrain();
	cout << endl << "To the west is a ";
	boardArray[y][x-1]->getTerrain();

}

void Tile::displayLocation() const
{
	cout << "You are standing in a " << terrain;
	if (treasure == 1)
		cout << "You see treasure nearby." << endl;
}

int Tile::getTerrain {return terrain;}

int Tile::getX {return xValue;}

int Tile::getY {return yValue;}
	





