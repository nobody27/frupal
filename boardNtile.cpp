/////////////////////////////////////////////////
// ATeam Jessica, Elyse, Max, Leior, John
// CS 300
// Spring 2019
// boardNtile.cpp
////////////////////////////////////////////////

//constructors destructors and functions of Board class


#include "GameManager.h"
#include "seeker.h"
#include "boardNtile.h"
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

Terrain::Terrain(string theName, 
								char theShortName, 
								unsigned int theExertion, 
								string theColor) : exertion(theExertion), 
				name(theName), 
				shortName(theShortName), 
				color(theColor)
{
}

void Terrain::display() const
{
				cout << color << name << RESET;
}

void Terrain::displayShortName() const
{
				cout << color << shortName << RESET;
}


//tile constructor
Tile::Tile(int x, int y, Terrain* theTerrain): xValue(x), 
				yValue(y),
				obstacle(NULL),
				terrain(theTerrain),
				visited(false)
{
				//make sure that terrain is not a null pointer
				assert(terrain);
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
								cout << "There is $" << 
												money << " gold here!! ";
				}
				else
				{
								cout << "There is no gold left here. ";
				} 
				if (treasureChar == 'n')
				{
								cout << "The Jewel is "<< MAGENTA << "not here. "<< RESET << endl;
				}
				else
				{
								cout << MAGENTA << "The Jewel is here!!!" << RESET << endl;
				}
}

void Tile::displayLocation() const
{
				cout << "You are standing in a ";
				terrain->display();
				cout << endl;

}



void Tile::printIslandTile(Tile* location)
{
				//terrain type
				if(!visited)
				{
								cout<<GRAY<< "X"<<RESET;
				}
				else
				{
								terrain->displayShortName();
				}
				//seeker location
				if (this == location)
				{
								cout << BOLDRED << "@" << RESET;
				}
				else
				{
								cout << GRAY <<"_"<<RESET;
				}
				//treasure E for excavation, or Letter for treasure type
				if(!visited)
				{
								cout <<GRAY<< "E"<<RESET;
				}
				else
				{
								cout << MAGENTA << treasureChar <<RESET;
				}
}

void Tile::printIslandTileR2(Tile* location)
{
				if(!visited) 
				{
								cout<<GRAY<< "O";
								cout << "XX"<<RESET; //unknown amount of money
				}
				else
				{
								if(obstacle) {
												cout << obstacle->symbol; 
								} else {
												cout << "o"; // no obstacle;
								}
								cout << "$" << money;
				}
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
				initTerrainMap();
				//init the board
				boardArray = new Tile**[boardSize];	
				for(int i=0; i<boardSize; ++i)
				{
								boardArray[i]= new Tile*[boardSize];
								for(int j=0; j<boardSize; ++j)
								{
												//preparation for options: if location exists in options
												//set according to it, otherwise set default
												int slope = -.3;
												int yInt = .8*boardSize;
												if(j > slope*i + yInt)
												{
																boardArray[i][j]=new Tile(i,j, terrainMap["forest"]);
												}
												else
												{	
																boardArray[i][j]=new Tile(i,j, terrainMap["grassy_meadow"]);
												}
								}
				}
				//add river
				putInRiver();
				//OBSTACLE TESTING *********
				boardArray[1][2]->obstacle = new Obstacle("BUSH", 5, 'B', true);
				boardArray[2][2]->obstacle = new Obstacle("ROCK", 10, 'R', false);
				//these lines below add Jewel
				Tile* jewelTile = randJewelTile();
				jewelTile->treasureChar = 'J';
				//use for testing how map looks
				//visitAllTiles();
}

void Board::putInRiver()
{
				int riverX = 0;
				int riverY = .8 * (boardSize-1);

				do
				{
								boardArray[riverX][riverY]->terrain = terrainMap["water"];
								if(rand()%2 ==0)
								{
												if(riverX<boardSize-1)
												{
																++riverX;
												}
								}
								else
								{
												if(riverY>0 ) 
												{
																--riverY;
												}
								}
				}while(riverX != boardSize-1 || riverY != 0);
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
				cout << "KEY:  Top left shows terrain type:"<<YELLOW<<"	G=Grassy Meadow," <<BLUE<<" B=Bog,"<< GREEN <<" F=Forrest,"<<CYAN<<" W=Water,"<<GRAY<<" X=Unrevealed"<< RESET<<endl;
				cout << "      Top center shows the SEEKER's location "<<BOLDRED << "@" << RESET;
				cout << "      Top right is the Excavation site(E). Reveals to " <<MAGENTA << "'n' none" << RESET <<" or "<<MAGENTA<< "'J' Jewel." <<RESET<<endl;
				cout << "      Bottom left shows obstacles. Bottom center shows money." <<endl;
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
				jewelX = (boardSize - 1 - rand1);
				int rand2 = (rand())%halfBoard;
				jewelY = (boardSize - 1 - rand2);
				cerr << "rand1" << rand1 <<endl;
				cerr << "rand2" << rand2 <<endl;
				cerr << "jewelX" << jewelX <<endl;
				cerr << "jewelY" << jewelY <<endl;

				return boardArray[jewelX][jewelY];
}

bool Board::onIsland(int x, int y)
{
				return (x >= 0 && x < boardSize && y >= 0 && y < boardSize );
}

void Board::visitLocationAndNeighbors(Tile* location, bool endRecursion)
{
				int x = location->xValue;
				int y = location->yValue;

				//this is only really needed for the first position in the
				//game and after jumping to the jewels but it's a good
				//sanity check
				assert(onIsland(x,y)); 
				boardArray[x][y]->visitTile();

				//show show info regarding tiles one step away
				if(onIsland(x, y+1)) boardArray[x][y+1]->visitTile();
				if(onIsland(x, y-1)) boardArray[x][y-1]->visitTile();
				if(onIsland(x+1, y)) boardArray[x+1][y]->visitTile();
				if(onIsland(x-1, y)) boardArray[x-1][y]->visitTile();
				if(endRecursion == true)
								return;

				//if seeker has binoculars show tiles two steps away
				if(gameMgr->theSeeker->hasBinoculars) 
				{
								if(onIsland(x, y+1)) visitLocationAndNeighbors(boardArray[x][y+1], true);
								if(onIsland(x, y-1)) visitLocationAndNeighbors(boardArray[x][y-1], true);
								if(onIsland(x+1, y)) visitLocationAndNeighbors(boardArray[x+1][y], true);
								if(onIsland(x-1, y)) visitLocationAndNeighbors(boardArray[x-1][y], true);
				}
}

void Board::displayLocation(Tile* location) 
{
				int x = location->xValue;
				int y = location->yValue;
				visitLocationAndNeighbors(location, false);
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

void Board::initTerrainMap()
{
				terrainMap["grassy_meadow"] = new Terrain("grassy_meadow", 'G', 1, YELLOW);
				terrainMap["bog"] = new Terrain("bog", 'B', 2, CYAN);
				terrainMap["forest"] = new Terrain("forest", 'F', 2, GREEN);
				terrainMap["water"] = new Terrain("water", 'W', 0, BLUE);


}

