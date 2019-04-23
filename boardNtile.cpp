/////////////////////////////////////////////////
// ATeam Jessica, Elyse, Max, Leior, John
// CS 300
// Spring 2019
// boardNtile.cpp
////////////////////////////////////////////////

//constructors destructors and functions of Board Terrain, and Tile classes

#include "seeker.h"
#include "boardNtile.h"
#include <vector>
#include <assert.h>
#include <string>

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
								cout<< "X";
				}
				else
				{
								cout<< terrain->getShortName();
				}
				cout << "_";
				cout << "E";
}

void Tile::visitTile()
{
				visited=true;
}


Board::Board(int size)    //default constructor 
{
	//init the terrain TODO - repleace with real configuration
	//for now add a default grassy meadow terrain
	string terrainName = "grassy_meadow";
	string terrainShortName = "G";
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
				cout<< "key:  top left space is terrain type: "<<endl;
				cout << "(G=Grassy Meadow, B=Bog, F=Forrest, X=terrain not yet revealed)" <<endl;
				cout << "top center space: empty unless Seeker is on it."<<endl;
				cout << "top right center space: E=Excavation site, until searched" <<endl;
				cout << "bottom three Xs have no current meaning."<< endl;
				cout << "could hold info about, obstacles, or ?" <<endl;
				//TODO note to team - spaces could hold info about tile, (obstacles, tools, food etc) 

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
				cout << "		";//left margin
				for(int i=0; i<size; ++i)
				{
								cout << "XXX";
								cout << "  ";
				}
				cout <<endl;
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

//add resources to repo either in options or initialization
void Board::addResource()
{
        //basic add to resource repository, cant test until gameplays merge
        string name;
        string relevantObstacle;

        cout << "tool name: ";
        cin >> name;
        cout << "relevant obstacle: ";
        cin >> relevantObstacle;

//        Tool newTool = Tool(name, relevantObstacle);
 //       resources.push_back(newTool);  
        return;
}
