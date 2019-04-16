//
//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//frupalMain.cpp

//constructors destructors and functions of Board and Tile classes

#include "boardNtile.h"

#include <assert.h>

using namespace std;

Terrain::Terrain(string theName, string theShortName) : name(theName), shortName(theShortName)
{
}

void Terrain::display()
{
	cout << "	Terrain: " << name << endl;
}


void Terrain::setTerrainType(string theName, string theShortName)
{
				name=theName;
				shortName=theShortName;
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

void Tile::printIslandTile()
{
				if(!visited)
				{
								cout<< "XX";
				}
				else
				{
								cout<< terrain->getShortName();
				}
				cout << "_";
				cout << "EX";
}

void Tile::visitTile()
{
				visited=true;
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
	string terrainShortName = "GM";
	terrainMap[terrainName] = new Terrain(terrainName, terrainShortName);
	
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

void Board::display() const
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

void Board::displayIsland(int size) const
{
				cout<< "Current island display: " <<endl<<endl;
				for(int j=(size-1); j>=0; --j)
				{
								displayRow(j, size);
				}
}

void Board::displayRow(int rowNumber, int size) const
{
				cout << endl;
				cout << "		"; //left margin
				int j=rowNumber;
				for(int i=0; i<size; ++i)
				{ 
								boardArray[i][j]->printIslandTile();
								cout << "  "; //space between tiles
				}
				cout << endl;
}


void Board::visitAllTiles()
{
				for(int i=0; i<boardSize; ++i)
				{
								for(int j=0; j<boardSize; ++j)
								{
									boardArray[i][j]->visitTile();
								}
				}
}


