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
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
using namespace std;

Terrain::Terrain(string theName, string theShortName, unsigned int theExertion) : exertion(theExertion), name(theName), shortName(theShortName)
{
}

void Terrain::display()
{
				cout << name;
}


void Terrain::setTerrainType(string theName, string theShortName, unsigned int theExertion)
{
				name=theName;
				shortName=theShortName;
				exertion=theExertion;
}

//by default set terrain to grassy meadow for now
Tile::Tile(int x, int y, Terrain* theTerrain): xValue(x), 
				yValue(y),
				obstacle(NULL),
				terrain(theTerrain),
				visited(false)
{
				//make sure that terrain is not a null pointer
				assert(terrain);
				//treasureName=("none"); //no treasure - later string withe description
				if(treasureChar != 'J') treasureChar = 'n';
				
				//make sure that the amount of money is not negative and also make sure
				//it is not more than one char long
				money = rand() % 10;
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
						money << "!!";
				} 
				else 
				{
					cout << "There is no gold left to find here.";
				} 
				if (treasureChar == 'n')
				{
				cout << "Bummer, the Jewel is not here. "<<endl;
				}
				else
				{
					cout << "The Jewel is here!!!" <<endl;
				}
				//cout << "There is an obstacle here, it is a __________." <<endl;
				//cout << "	" << (visited ? "visited by seeker" : "undiscovered") << endl;
}

void Tile::displayLocation() const
{
				cout << "You are standing in a ";
				terrain->display();
				cout << endl;
				if(treasureChar == 'J')
				{
								cout << GREEN <<  "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
								cout << BLUE << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
								cout << BOLDRED << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
								cout << YELLOW << "YOU WIN!!!!!!!!!!!!!!!!!!!!!" <<endl;
								cout << GREEN << "WELL DONE! You are the greatest treasure seeker ever and you have found the jewel!" <<RESET<<endl;
								//TODO set configuration to exit the game
				}
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
								cout << MAGENTA << treasureChar <<RESET;
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
					if(obstacle) {
						cout << obstacle->symbol; 
					} else {
						cout << "o"; // no obstacle;
						
					}
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
				string terrainName = "grassy_meadow";
				string terrainShortName = "G";
				terrainMap[terrainName] = new Terrain(terrainName, terrainShortName, 1);
				terrainMap["bog"] = new Terrain("bog", "B", 2);
				terrainMap["forest"] = new Terrain("forest", "F", 2);

				//init the board
				boardArray = new Tile**[boardSize];	
				for(int i=0; i<boardSize; ++i)
				{
								boardArray[i]= new Tile*[boardSize];
								for(int j=0; j<boardSize; ++j)
								{
												//perparation for options: if location exists in options
												//set according to it, otherwise set default
												if(j>= -.3*boardSize + .8*boardSize)
												{
												boardArray[i][j]=new Tile(i,j, terrainMap["forest"]);
												}
												else
											{	
												boardArray[i][j]=new Tile(i,j, terrainMap["grassy_meadow"]);
											}
								}
				}
        //OBSTACLE TESTING *********
        boardArray[1][1]->obstacle = new Obstacle("BUSH", 5, 'B', true);
        boardArray[2][2]->obstacle = new Obstacle("ROCK", 10, 'R', false);
				//functions here to add Jewel
				Tile* jewelTile = randJewelTile();
				jewelTile->treasureChar = 'J';
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

				cout <<endl;
				cout << "KEY:  Top left shows terrain type:	G=Grassy Meadow, B=Bog, F=Forrest, W=Water, X=Unrevealed"<<endl;
				cout << "      Top center shows the SEEKER's location "<<BOLDRED << "@" << RESET;
				cout << "      Top right is the Excavation site(E). Reveals to 'n' none or 'J' Jewel." <<endl;
				// cout << "  Bottom left is for obstacles." <<endl<<endl;
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

//randJewelTile return a Tile pointer that is in a random location in the top right quadarnt of the board
//it takes no input
//later could add cases to also make it possible for Jewel to be in top left or bottom right
Tile* Board::randJewelTile()
{
				int jewelX = 0;
				int jewelY = 0;
				int halfBoard = .5*boardSize; //this should round down and give an int
				int rand1 = (rand())%halfBoard; // rand1 will be a random int between 0 and halfBoard so that when subtracted
				//from boardsize will be in top right quadrant - jewel will be in the quarter of the board furthest from the start
				jewelX = boardSize - 1 - rand1;
				int rand2 = (rand())%halfBoard;
				jewelY = boardSize - 1 - rand2;
				return boardArray[jewelX][jewelY];
}
				
void Board::visitLocationAndNeighbors(Tile* location)
{
		int x = location->xValue;
		int y = location->yValue;
		
		boardArray[x][y]->visitTile();
		if (y+1 < boardSize) {
				boardArray[x][y+1]->visitTile();
		}
		if (y > 0) {
				boardArray[x][y-1]->visitTile();
		}
		if (x+1 < boardSize) {
				boardArray[x+1][y]->visitTile();
		}
		if (x > 0) {
				boardArray[x-1][y]->visitTile();
		}

}

void Board::displayLocation(Tile* location) 
{
				int x = location->xValue;
				int y = location->yValue;
				visitLocationAndNeighbors(location);
				location->displayLocation();
				if (y+1 >= boardSize) {
								cout << "To the north lies ocean" << endl;
				} else {
								cout << "To the north is a ";
								boardArray[x][y+1]->tileDisplay();
				}
				if (y-1 < 0) {
								cout << "To the south lies ocean" << endl;
				} else {
								cout << "To the south is a ";
								boardArray[x][y-1]->tileDisplay();
				}
				if (x+1 >= boardSize) {
								cout << "To the east lies ocean" << endl;
				} else {
								cout << "To the east is a ";
								boardArray[x+1][y]->tileDisplay();
				}
				if (x-1 < 0) {
								cout << "To the west lies ocean";
				} else {
								cout << "To the west is a ";
								boardArray[x-1][y]->tileDisplay();
				}
}


