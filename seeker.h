 h/ATeam Jessica, Elyse, Max, Leior, John
 //cs300
 //April 10, 2019
 //seeker.h

#ifndef SEEKER_H
#define SEEKER_H

#include <vector>

using namespace std;

//forward declaration of obstacle class
class obstacle;

//a class for tools that exist on frupal and that the seeker may take/purchace
//TODO should this be moved to the board configuration along with the obstacles?
//the tool can be used on an obstacle (TBD maybe for a list of obstacles in the future)
//the tool may be a one time use - e.g. a power bar - or multiple use object
class Tool {
	public:
		//constructors
    Tool(string theName, string obstacleName);
		Tool(string theName, string obstacleName, int energySaved, bool
    singleUse, int price, int quantity);
		//use the tool
		//check that it can be used on the relevant obstacle type
		//if the tool is singleUse make sure to remove it from the seeker
		void apply(obstacle* currentObstacle);
	private:
		string name;
		string relevantObstacle;
    int energySaved;
		bool singleUse;
    int price;
    int quantity;
};

class SeekerConfigurations {
public:
	SeekerConfigurations()
	Tile* theLocation;
	int theEnergy;
	int themoney;
	vector<Tool> theInventory;

};

class Seeker
{
  public:
    //constructor
    Seeker();
    Seeker(Tile* theLocation, int theEnergy, int theMoney, vector<Tool> theInventory);
   
    //movement functions
    Tile* getLocation() const;
    bool setLocation(int xVaule, int yValue);
    void displayLocation();
    void display(); 
    void look/*direction*/(); //TODO set enum for North, South, East, West
    void move(/*direction*/); //

    //items
    //TODO need access to tools in the event of a single use tool
    bool useTool();
    //check we have enough money and discount the total money according to price
    bool buyTool();

    Tile* location;
    int energy;
    int money;
    vector<Tool> inventory;
};
 
#endif

