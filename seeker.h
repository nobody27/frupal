 //ATeam Jessica, Elyse, Max, Leior, John
 //cs300
 //April 10, 2019
 //seeker.h

#ifndef SEEKER_H
#define SEEKER_H

#include <iostream>

using namespace std;

//forward declaration of obstacle class
//class obstacle;

//a class for tools that exist on frupal and that the seeker may take/purchace
//TODO should this be moved to the board configuration along with the obstacles?
//the tool can be used on an obstacle (TBD maybe for a list of obstacles in the future)
//the tool may be a one time use - e.g. a power bar - or multiple use object
/*
class Tool {
	public:
		//constructor
		Tool(string theName, int thePrice, obstacle* relevantObstacle, bool singleUse);
		//use the tool
		//check that it can be used on the relevant obstacle type
		//if the tool is singleUse make sure to remove it from the seeker
		void apply(obstacle* obstacle);
	private:
		string name;
		int price;
		obstacle* relevantObstacle;
		bool singleUse;
};
*/

class Seeker
{
  public:
    //for easy lookup and access of tools by configurable name
    //TBD we may need to add an optional quantity of each tool
    //typedef unordered_map<string,Tool> ToolMap;
    //constructor
    Seeker(Board* theIsland); //default constructor
    //Seeker(Tile* theLocation, int theEnergy, int theMoney, ToolMap theTools);
   
    //movement functions
    //bool setLocation(int xValue, int yValue);
    //void displayLocation();
    void display(); 
    //void look/*direction*/(); //TODO set enum for North, South, East, West
    void move(int x, int y); //
    Tile* getLocation() {return location;}


    //TODO if we need getters and setters for everything why not just make it public
    //Don't worry, Karla isn't watching ;)
    //get/set energy
    //int getNrg();
    //bool setNrg(int nrg);

    //get/set money
    //int getMoney();
    //bool setMoney(int money);

    //items
    //TODO need access to tools in the event of a single use tool
   // bool useTool(Tool theTool);
    //check we have enough money and discount the total money according to price
    //bool buyTool(Tool theTool);

  private:
    Tile* location;
    Board* theIsland;
    int energy;
    int money;
    //ToolMap tools;
};
 
#endif

