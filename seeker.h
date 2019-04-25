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
#include "resources.h"

//forward declarations
class GameManager;
class Obstacle;
class Tile;


using namespace std;

class SeekerOptions {
public:
	SeekerOptions(GameManager* gameManager);
	int x;
	int y;
	int theEnergy;
	int theMoney;
	vector<Tool*> theInventory;
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
    void displayTools();
    void move(direction_t direction); //

	void addTool(Tool* newTool);
    //items
    //TODO need access to tools in the event of a single use tool
    //TODO bool useTool();
    //changed this to addTool for scenarios where tools are found and not
    //purchased
    //TODO bool addTool();

    Tile* location;
    int energy;
    int money;
    vector<Tool*> inventory;
  private:
	GameManager* gameMgr;
	Board* theIsland;
};
 
#endif

