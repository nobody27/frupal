//
//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//frupalMain.cpp

//constructors destructors and functions of Board and Tile classes

#include "boardNtile.h"

#include <assert.h>

using namespace std;

Terrain::Terrain(string theName) : name(theName)
{
}

void Terrain::display()
{
	cout << "	Terrain: " << name << endl;
}

//by default set terrain to grassy meadow for now
Tile::Tile(int x, int y, Terrain* theTerrain): xValue(x), 
					yValue(y),
					terrain(theTerrain),
					visited(false)
{
	//make sure that terrain is not a null pointer
	assert(terrain);
	treasure=("Nothing here! Better luck next time."); //no treasure - later string withe description
}

void Tile::tileDisplay()
{
	cout << "	Position: (" << xValue << "," <<
				yValue << ")" << endl;
	terrain->display();
	cout << "	Treasure: " << treasure<<endl;
	cout << "	" << (visited ? "visited by seeker" : "undiscovered") << endl;
}



/*
Board::Board()
{
				Board(10);
}
*/

Board::Board(int size)
{
	//init the terrain TODO - repleace with real configuration
	//for now add a default grassy meadow terrain
	string terrainName = "grassy_meadow";
	terrainMap[terrainName] = new Terrain(terrainName);
	
	//init the board
	boardSize = size;
	boardArray = new Tile**[size];	
	for(int i=0; i<size; ++i)
	{
		boardArray[i]= new Tile*[size];
		for(int j=0; j<size; ++j)
		{
			boardArray[i][j]=new Tile(i,j, terrainMap["grassy_meadow"]);
		}
	}
}

Board::~Board()
{
	delete[] boardArray;
	//delete all saved terrain types
	for (auto terrainPair : terrainMap)
	{
		delete terrainPair.second;
	}
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

void Board::displayLocation(Tile* location) const
{
	int x = location->getX();
	int y = location->getY();
	location->displayLocation();
	if (y+1 >= boardSize)
		cout << endl << "To the north lies ocean";
	else {
		cout << endl << "To the north is a ";
		boardArray[x][y+1]->getTerrain();
	}
	if (y-1 < 0)
		cout << endl << "To the south lies ocean";
	else {
		cout << endl << "To the south is a ";
		boardArray[x][y-1]->getTerrain();
	}
	if (x+1 >= boardSize)
		cout << endl << "To the east lies ocean";
	else {
		cout << endl << "To the east is a ";
		boardArray[x+1][y]->getTerrain();
	}
	if (x-1 < 0)
		cout << endl << "To the west lies ocean";
	else {
		cout << endl << "To the west is a ";
		boardArray[x-1][y]->getTerrain();
	}

}

void Tile::displayLocation() const
{
	cout << "You are standing in a " << terrain->getTerrain();
	//TODO add in more features of location
}

	





