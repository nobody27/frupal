
////////////////////////////////////////////////
// ATeam Jessica, Elyse, Max, Leior, John
// CS 300
// Spring 2019
// boardNtile.cpp
////////////////////////////////////////////////

//constructors destructors and functions of Board class


#include "GameManager.h"
#include "seeker.h"
#include "boardNtile.h"
#include "colors.h"
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

Terrain::Terrain(string theName, 
								char theShortName, 
								unsigned int theExertion, 
								string theColor) : exertion(theExertion), 
				color(theColor),
				name(theName), 
				shortName(theShortName)
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
								cout << "There is $" << money << " gold here!! ";
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
								cout << MAGENTAonYELLOW << "The Jewel is here!!!" << RESET << endl;
				}
}

void Tile::displayLocation() const
{
				cout << "You are standing in a ";
				terrain->display();
				cout << endl;

}



void Tile::printIslandTile(Tile* location, string command)
{
				if (command == "full" || command == "endgame")
				{
								if (this == location)
												cout << BOLDRED << "@" << RESET;
								else if (treasureChar == 'J' && visited == true)
												cout << MAGENTAonYELLOW << treasureChar << RESET;
								else if (!visited)
												cout << GRAY << "X" << RESET;
								else
												terrain->displayShortName();
				}
				else
				{ 
								//terain 
								if(!visited)
												cout<<GRAY<< "X"<<RESET;
								else
												terrain->displayShortName();
								//seeker location
								if (this == location)
												cout << BOLDRED << "&" << RESET;
								else
												cout << GRAY <<"_"<<RESET;
								//treasure E for excavation, or Letter for treasure type
								if(!visited)
												cout <<GRAY<< "E"<<RESET;
								else
									if(treasureChar == 'J'){
										cout << MAGENTAonYELLOW << treasureChar << RESET;
									}else{
										cout << MAGENTA << treasureChar <<RESET;
									}
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
									if(!obstacle->name.compare("WATER")){
										cout << BLUE << obstacle->symbol << RESET;
									}else{	
												cout << OBSTACLE_COLOR << obstacle->symbol << RESET; 
									}
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

								retVal = money;
								money = 0;
				}
				return retVal;
}


//init by default to size of 10 but allow users to override the default
BoardOptions::BoardOptions(GameManager* gameManager) : size(10), gameMgr(gameManager)
{
				randomSeed = time(0);
}


Board::Board(GameManager* gameManager, const BoardOptions& options) : 
				gameMgr(gameManager),
				boardSize(options.size),
				randomSeed(options.randomSeed)
{
				srand(randomSeed);
				cerr << "seed = " << randomSeed <<endl;
				initTerrainMap();
				//init the board
				boardArray = new Tile**[boardSize];	
				float varianceSlope1 = (.1)*(rand()%11);  //this is a number from 0 to 1.0. below will subtract it from slope -.5
				float varianceSlope2 = rand()%4; //this is a number 0, 1, 2, or 3. below will add it to slope2 of 1
				bool forrestAbove =  rand()%2;
				for(int i=0; i<boardSize; ++i)
				{
								boardArray[i]= new Tile*[boardSize];
								for(int j=0; j<boardSize; ++j)
								{
												//preparation for options: if location exists in options
												//set according to it, otherwise set default
												float slope = (-.5);
												float xVal = i; //now i have a float to use (instead of int i)
												float yInt = .5*boardSize;
												int checkValue = ((slope-varianceSlope1)*xVal + yInt);  //having floats in calculation avoids too much rounding
												float slope2 = 1;
												float yInt2 = -.6*boardSize;
												int checkValue2 = ((slope2+varianceSlope2)*xVal + yInt2);  //having floats in calculation avoids too much rounding
												if(j >= checkValue)
												{
																if(forrestAbove)
																{
																				if(j <= checkValue2)
																				{
																								boardArray[i][j]= new Tile(i,j, terrainMap["bog"]);
																				}
																				else
																				{
																								boardArray[i][j]=new Tile(i,j, terrainMap["forest"]);
																				}
																}
																else
																{
																				if(j > checkValue2)
																				{
																								boardArray[i][j]= new Tile(i,j, terrainMap["bog"]);
																				}
																				else
																				{
																								boardArray[i][j]=new Tile(i,j, terrainMap["forest"]);
																				}
																}
												}
												else
												{	
																boardArray[i][j]=new Tile(i,j, terrainMap["grassy_meadow"]);
												}
								}
				}
				//RIVER*******
				putInRiver();
				//OBSTACLES *********
				putInObstacles();
				//these lines below add Jewel
				jewelTile = randJewelTile();
				jewelTile->treasureChar = 'J';
				//use for testing how map looks
				//visitAllTiles();
}

void Board::putInObstacles()
{
				// we want the percentage of tiles with obstacles to be approximately the same independent of boardSize
				// (approx 50% for now)
				// tile percentage variable
				// so numberEach (the number of each type of obstacle) needs to scale with teh square of boardsize
				// numberEach = boardSize*boardSize times obstaclePercentage and by 4 because four types of obstaclesA
				float obstacleDensity = (gameMgr->obstacleDensity)/100.0;
				int obstacleCount = gameMgr->resourcesOptions->theObstacles.size();
				int numberEach = boardSize*boardSize*obstacleDensity/obstacleCount;

for(auto it = begin(gameMgr->resourcesOptions->theObstacles); it != end(gameMgr->resourcesOptions->theObstacles); ++it){
	if(it->name.compare("WATER") != 0){
		for(int i = 0; i < numberEach; ++i){
			int rand1 = rand()%boardSize;
			int rand2 = rand()%boardSize;
			boardArray[rand1][rand2]->obstacle = new Obstacle(it->name, it->energyCost, it->symbol, it->removable);
			if(!it->name.compare("VORTEX")){
				i++;
			}
		}
	}else{
		for(int i = 0; i < boardSize; i++){
			for(int j = 0; j < boardSize; j++){
				if(boardArray[i][j]->terrain->getShortName() == 'W'){
					boardArray[i][j]->obstacle = new Obstacle(it->name, it->energyCost, it->symbol, it->removable);
				}
			}
		}
	}
}
/*
				for(int i=0; i<numberEach; ++i) //BUSHES

				{
								int rand1 = rand()%boardSize;
								int rand2 = rand()%boardSize;
								//if(boardArray[rand1][rand2]->terrain->getShortName() != W)
								boardArray[rand1][rand2]->obstacle = new Obstacle("BUSH", 5, 'B', true);
				}
				for(int i=0; i<numberEach; ++i) //ROCKS
				{
								int rand1 = rand()%boardSize;
								int rand2 = rand()%boardSize;
								boardArray[rand1][rand2]->obstacle = new Obstacle("ROCK", 10, 'R', false);
								//if(boardArray[rand1][rand2]->terrain->getShortName() != W) 
				}
				for(int i=0; i<numberEach; ++i) //TREES
				{
								int rand1 = rand()%boardSize;
								int rand2 = rand()%boardSize;
								boardArray[rand1][rand2]->obstacle = new Obstacle("TREE", 10, 'T', false);
				}
				for(int i=0; i<numberEach; ++i) //Vortex / vorticies
				{
								int rand1 = rand()%boardSize;
								int rand2 = rand()%boardSize;
								boardArray[rand1][rand2]->obstacle = new Obstacle("VORTEX", 100, 'V', false);
				}
*/
}


void Board::putInRiver()
{
				int riverX = 0;
				int riverY = .8 * (boardSize-1);
				boardArray[riverX][riverY]->terrain = terrainMap["water"];
				do
				{
								if(rand()%10 >= 5)
								{
												if(riverX<boardSize-2)
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
								boardArray[riverX][riverY]->terrain = terrainMap["water"];
				}while(riverX != boardSize-1 && riverY != 0);
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
				int halfBoard = boardSize/2; //this rounds down and is the int <= half
				int rand1 = (rand())%halfBoard; // rand1 will be a random int between 0 and halfBoard so that when subtracted
				int rand2 = (rand())%halfBoard;
				int Case = rand()%3;    //case is a reserved word, so I used Case
				if (Case == 0)  //top right quadrant
				{
								jewelX = (boardSize - 1 - rand1);
								jewelY = (boardSize - 1 - rand2);
				}
				else if (Case == 1)  //top left quadrant
				{
								jewelX = rand1;
								jewelY = (boardSize - 1 - rand2);
				}
				else if (Case == 2)  //bottom right quadrant
				{
								jewelX = (boardSize - 1 - rand1);
								jewelY = rand2;
				}
				assert(jewelX >=0 && jewelX < boardSize); //TODO is this standard good practice or a check we dont need?
				assert(jewelY >=0 && jewelY < boardSize);
				assert( boardArray[jewelX][jewelY] ); //make sure it's not a null ptr
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
				terrainMap["water"] = new Terrain("water", 'W', 0, CYANonBLUE);
}

//TODO these values should be fields in Board
void Board::followVars(int&posX, int&posY, int&minX, int&maxX, int&minY, int&maxY) const
{
				int followSize = 9; //TODO make this global or configurable. best result if odd number
				//deal with small boards
				if(followSize > boardSize + 2) {
								followSize = boardSize + 2;
				}
				int leftMargin = followSize/2; //half of size rounded down
				int rightMargin = followSize - leftMargin -1;


				posX = gameMgr->theSeeker->getLocation()->xValue;
				posY = gameMgr->theSeeker->getLocation()->yValue;

				minX = posX - leftMargin;
				maxX = posX + rightMargin;
				if (minX < -1) {
								minX = -1;
								maxX = followSize - 2;
				} else if (maxX > boardSize) {
								maxX = boardSize;
								minX = maxX - followSize + 1;
				}
				assert(minX >= -1);
				assert(maxX - minX <= followSize);

				//TODO this should be a method that is called once for x and again for y
				minY = posY - leftMargin;
				maxY = posY + rightMargin;
				if (minY < -1) {
								minY = -1;
								maxY = followSize - 2;
				} else if (maxY > boardSize) {
								maxY = boardSize;
								minY = maxY - followSize + 1;
				}
				assert(minY >= -1);
				assert(maxY - minY <= followSize);

				assert(followSize <= boardSize +2);
				return;
}

void Board::displayIsland(string command) const
{
				int posX, posY, minX, maxX, minY, maxY;
				if(command == "local") {
                                cout << endl << "Your current location:" << endl;
								followVars(posX, posY, minX, maxX, minY, maxY);
				} else {
								minY = -1;
								maxY = boardSize;
				}

				if (command != "local")
								cout << "The Island of Frupal:" << endl;
				for(int j=maxY; j>=minY; --j)
				{
								displayRow(j, command);
				}
				cout <<endl;
				cout << GRAY << "Terrain Key:       " << GRAY << "OCEAN = " << BLUE << (command == "local" ? "'~~~'" : "'~'") << RESET;
				cout << GRAY <<  "    GRASSY MEADOW = " << YELLOW << "'G'" << GRAY << "    BOG = " << CYAN << "'B'" << GRAY << "    FORREST = " << GREEN << "'F'" << GRAY << "    WATER = " << CYANonBLUE << "'W'" << RESET;
				cout << endl << GRAY << "SEEKER's Location:" << BOLDRED <<" '&' " << RESET;
				if (command == "local")
				{
								cout << GRAY << endl << "Excavation Site:   'E' reveals to " << MAGENTA << "'n' none" << RESET << GRAY << " or " << MAGENTA << "'J' Jewel." << RESET;
				}
                cout << endl;
				gameMgr->resourcesOptions->printObstacleKey();
                cout << RESET;
}

void Board::displayRow(int rowNumber, string command) const
{
				string ocean("~"); 
				string blueOcean1 = BLUE + ocean + RESET;
				string blueOcean3 = BLUE + ocean + ocean + ocean + RESET;
				int posX, posY, minX, maxX, minY, maxY;
				if(command == "local") {
								followVars(posX, posY, minX, maxX, minY, maxY);
				} else {
								minX = -1;
								maxX = boardSize;
				}

				assert(rowNumber >= -1);
				assert(rowNumber <= boardSize);
				assert(minX >= -1);
				assert(maxX <= boardSize);
				int j=rowNumber;
				cout << endl;
				cout << "		"; //left margin
				for(int i=minX; i<=maxX; ++i)
				{ 
								if(i>=0 && i<boardSize && j>=0 && j<boardSize) 
								{
									boardArray[i][j]->printIslandTile(gameMgr->theSeeker->location, command);
								} else if(command == "local") {
									cout << blueOcean3;	
								} else {
									cout <<blueOcean1; //endgame
								}
								if (command == "local")
								{
									cout << "  "; //space between tiles
								}
				}
				//cout << endl;
				if (command == "local")
				{
								cout << endl;
								cout << "		";//left margin
								for(int i=minX; i<=maxX; ++i)
								{
										if(i>=0 && i<boardSize && j>=0 && j<boardSize) 
										{
											boardArray[i][j]->printIslandTileR2(gameMgr->theSeeker->location);
										} else {
											cout << blueOcean3;	
										}
										cout << "  "; //space between tiles
								}
								cout << endl;
				}
}

