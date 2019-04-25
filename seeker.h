 //ATeam Jessica, Elyse, Max, Leior, John
 //cs300
 //April 10, 2019
 //seeker.h

#ifndef SEEKER_H
#define SEEKER_H
#include <string>
#include <vector>

//#include "GameManager.h"
#include "boardNtile.h"

//forward declarations
class GameManager;
class Obstacle;
class Tile;


using namespace std;


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

    //TODO add copy constructor for tools for adding and reomving from vectors

		//use the tool
		//check that it can be used on the relevant obstacle type
		//if the tool is singleUse make sure to remove it from the seeker
		void apply(Obstacle* currentObstacle);
	private:
		string name;
		string relevantObstacle;
    int energySaved;
		bool singleUse;
    int price;
    int quantity;
};

class SeekerOptions {
public:
	SeekerOptions(GameManager* gameManager);
	int x;
	int y;
	int theEnergy;
	int theMoney;
	vector<Tool> theInventory;
private:
	GameManager* gameMgr;
};

class Seeker
{
  public:
	//enum for board directions
	enum direction_t {NORTH, SOUTH, EAST, WEST};
	
    //constructor
  Seeker(GameManager* gameManager, const SeekerOptions& seekerOptions);
   
    //movement functions
    Tile* getLocation() const {return location;}
    bool setLocation(int xValue, int yValue);
    void displayLocation();
    void display(); 
    void move(direction_t direction); //

	void addTool(Tool newTool);
    //items
    //TODO need access to tools in the event of a single use tool
    //TODO bool useTool();
    //changed this to addTool for scenarios where tools are found and not
    //purchased
    //TODO bool addTool();

    Tile* location;
    int energy;
    int money;
    vector<Tool> inventory;
  private:
	GameManager* gameMgr;
	Board* theIsland;
};
 
#endif

