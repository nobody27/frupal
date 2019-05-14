/////////////////////////////////////////////////
// ATeam Jessica, Elyse, Max, Leior, John
// CS 300
// Spring 2019
// boardNtile.cpp
////////////////////////////////////////////////

//constructors destructors and functions of Board Terrain, and Tile classes

#include "GameManager.h"
#include "seeker.h"
#include "boardNtile.h"
#include <vector>
#include <assert.h>
#include <string>
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDRED "\033[31;1m"

using namespace std;

Terrain::Terrain(string theName, string theShortName) : exertion(1), name(theName), shortName(theShortName)
{
}

/*void Terrain::display() //TODO is this function used by anything?
	{
	cout << "	Terrain: " << name << endl;
	}*/

void Terrain::display()
{
				cout << name;
}


void Terrain::setTerrainType(string theName, string theShortName)
{
				name=theName;
				shortName=theShortName;
}

//by default set terrain to grassy meadow for now
Tile::Tile(int x, int y, Terrain* theTerrain): xValue(x), 
				yValue(y),
				money(1), //TODO randomize this
				terrain(theTerrain),
				//for now we find one unit of money on each new tile
				visited(false),
        obstacle(NULL)
{
				//make sure that terrain is not a null pointer
				assert(terrain);
				treasureName=("none"); //no treasure - later string withe description
				//make sure that the amount of money is not negative and also make sure
				//it is not more than one char long
				assert(money >= 0 && money <=9);
}


Terrain* Tile::getTerrain()
{
				return terrain;
}


//for use in the "to the North lies ..." etc  should display Terrain, any obstacle, any treasure
void Tile::tileDisplay() const
{
				terrain->display();
				cout << ". ";
				if(money) 
				{	
					cout << "There is gold here with a value of $" << 
						money << "!!" << endl;
				} 
				else 
				{
					cout << "There is no gold left to find here." << endl;
				} 
				if (treasureName == "none")
				{
				cout << "Bummer, there is no treasure here. ";
				}
				else
				{
					cout << "There is treasure here!!!!!! The treasure is " << treasureName<< ". ";
				}
				cout << "There is an obstacle here, it is a __________." <<endl;
				//cout << "	" << (visited ? "visited by seeker" : "undiscovered") << endl;
}

void Tile::displayLocation() const
{
				cout << "You are standing in a ";
				terrain->display();
}



void Tile::printIslandTile(Tile* location)
{
				//terrain type
				if(!visited)
				{
								cout<< "X";
				}
				else
				{
								cout << YELLOW << terrain->getShortName() << RESET;
				}
				//seeker location
				if (this == location)
				{
								cout << BOLDRED << "@" << RESET;
				}
				else
				{
								cout << "_";
				}
				//treasure E for excavation, or Letter for treasure type
				if(!visited)
				{
								cout << "E";
				}
				else
				{
								cout << "n"; //treasureLetter;
				}
}

void Tile::printIslandTileR2(Tile* location)
{
				assert(money >= 0 && money <=9);
				//obstacle O or Letter for obstacle type
				if(!visited) 
				{
					cout<< "O";
					cout << "X"; //unknown amount of money
				}
				else
				{
					cout<< "o"; // later obstacleLetter;
					cout << money;
				}
				//space to expand functionality
				cout << "X";
}


void Tile::visitTile()
{
				visited=true;
}

int Tile::takeMoney()
{
	int retVal = 0;
	if(money) 
	{
		cout << "You just found $" << money << endl;
		retVal = money;
		money = 0;
	}
	else 
	{
		cout << "No money here, keep looking" << endl;
	}
	return retVal;
}

//init by default to size of 10 but allow users to override the default
BoardOptions::BoardOptions(GameManager* gameManager) : size(10), gameMgr(gameManager)
{
}


Board::Board(GameManager* gameManager, const BoardOptions& options) : 
				gameMgr(gameManager),
				boardSize(options.size)
{
				//init the terrain TODO - repleace with real configuration
				//for now add a default grassy meadow terrain
				string terrainName = "grassy_meadow";
				string terrainShortName = "G";
				terrainMap[terrainName] = new Terrain(terrainName, terrainShortName);

				//init the board
				boardArray = new Tile**[boardSize];	
				for(int i=0; i<boardSize; ++i)
				{
								boardArray[i]= new Tile*[boardSize];
								for(int j=0; j<boardSize; ++j)
								{
												//perparation for options: if location exists in options
												//set according to it, otherwise set default
												boardArray[i][j]=new Tile(i,j, terrainMap["grassy_meadow"]);
								}
				}
        //OBSTACLE TESTING *********
        boardArray[1][1]->obstacle = new Obstacle("BUSH", 5, 'B', true);
        boardArray[2][2]->obstacle = new Obstacle("ROCK", 10, 'R', false);
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

void Board::displayIsland() const
{

				for(int j=(boardSize-1); j>=0; --j)
				{
								displayRow(j);
				}

				cout << "Key:"<<endl;
				cout << "	Top left space is terrain type:	G=Grassy Meadow, B=Bog, F=Forrest, W=Water, X=Unrevealed"<<endl;
				cout << "	Top center is _ unless seeker is there. SEEKER is '@'." <<endl; 
				cout << "	Top right is for treasure. E=Excavation site until searched" <<endl;
				cout << "	Bottom left is for obstacles." <<endl<<endl;
				//TODO note to team - spaces could hold info about tile, (obstacles, tools, food etc) 
				// display seeker

}

void Board::displayRow(int rowNumber) const
{
				cout << endl;
				cout << "		"; //left margin
				int j=rowNumber;
				for(int i=0; i<boardSize; ++i)
				{ 
								boardArray[i][j]->printIslandTile(gameMgr->theSeeker->location);
								cout << "  "; //space between tiles
				}
				cout << endl;
				cout << "		";//left margin
				for(int i=0; i<boardSize; ++i)
				{
								boardArray[i][j]->printIslandTileR2(gameMgr->theSeeker->location);
								cout << "  "; //space between tiles
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

Tile* Board::getLocation(int x, int y) const {
				if(x<0 || y<0 || x>=boardSize || y>=boardSize) {
								assert(false);
								return nullptr;
				}
				return boardArray[x][y];
}


void Board::displayLocation(Tile* location) 
{
				int x = location->xValue;
				int y = location->yValue;
				location->displayLocation();
				if (y+1 >= boardSize)
								cout << endl << "To the north lies ocean" << endl;
				else {
								//cerr <<endl << "Now checking new displayTile() function" <<endl;
								boardArray[x][y+1]->visitTile();
								cout << endl << "To the north is a ";
								boardArray[x][y+1]->tileDisplay();
				}
				if (y-1 < 0)
								cout << endl << "To the south lies ocean" << endl;
				else {
								boardArray[x][y-1]->visitTile();
								cout << endl << "To the south is a ";
								boardArray[x][y-1]->tileDisplay();
				}
				if (x+1 >= boardSize)
								cout << endl << "To the east lies ocean" << endl;
				else {
								boardArray[x+1][y]->visitTile();
								cout << endl << "To the east is a ";
								boardArray[x+1][y]->tileDisplay();
				}
				if (x-1 < 0)
								cout << endl << "To the west lies ocean" << endl;
				else {
								boardArray[x-1][y]->visitTile();
								cout << endl << "To the west is a ";
								boardArray[x-1][y]->tileDisplay();
				}
}


