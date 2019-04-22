

//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 10, 2019
//boardNtile.h

#ifndef BOARD_N_TILE_H
#define BOARD_N_TILE_H

using namespace std;
#include <iostream>
//#include <cctype>
#include <cstring> //why is this needed?
//#include <cstdlib>
#include <string> //why is this needed?
#include <unordered_map>

//for now this class is used for type safety not to confuse terrain
//types with (for example) obstacle types. 
//but more fields will be needed and it will be easy to add them 
class Terrain {
	public:
		//constructor
		Terrain(string theName, string theShortName);
		//TODO - add constructor that configures all variables
		void display();
		const string& getName() const {return name;}
		const string& getShortName() const {return shortName;}
		void setTerrainType(string theName, string theShortName);

	private:
		string name;
		string shortName;
};

//a tile takes up a single location on the board and includes all the
//relavent information regarding what exists in that location
//(perhaps with the exception of whether or not the seeker is there)
class Tile
{
	public:
		Tile(int xValue, int yValue, Terrain* theTerrain); //constructor
		//~Tile();
		void tileDisplay();
    void printIslandTile();
		void visitTile();

	private:
		int xValue;
		int yValue;
		Terrain* terrain;
		string treasure;
		bool visited; //has the seeker visited this tile
		
};

////options for configuring the board////
class BoardOptions {
public:
	BoardOptions();
	int size;
};


//the game has a single board that represents the island of frupal
//this board is a grid of locations or "tiles"
class Board 
{
	public:
		//Board(); //constructor - this default creates a 10x10 board. Calls Board(10)
		Board(int size=10); //constructor - argument from user sizeBoardxsizeBoard
		~Board();
		void display() const;
    void displayIsland(int size) const;
		void displayRow(int rowNumber, int size) const;
		void visitAllTiles(); //reveal all for working display for coders
	  	
	private:
		int boardSize;
		Tile*** boardArray;
		unordered_map<string, Terrain*> terrainMap;
};
#endif //BOARD_N_TILE_H
