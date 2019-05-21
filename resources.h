 //ATeam Jessica, Elyse, Max, Leior, John
 //cs300
 //April 10, 2019
 //resources.h

#ifndef RESOURCES_H
#define RESOURCES_H
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class GameManager;
//obstacle class contains
class Obstacle{
	public:
	string name;	//a name, which must match the relevantObstacle field in the tool,
	int energyCost;	//the additional energy cost imposed by the obstacle,
	char symbol;	//the symbol that the obstacle will display on the map,
	bool removable;	//whether or not the obstacle is removable, e.g. water is not
	//default constructor
	Obstacle(string obstacleName, int cost, char mapSymbol, bool isRemovable);
	//display this obstacle. Used in configuration
	void display();
};
class Tile;

class Tool {
	public:
		//constructors
    Tool(string theName, string obstacleName);
		Tool(string theName, string obstacleName, int energySaved, bool
    singleUse, int price, int quantity);
		//use the tool
		//check that it can be used on the relevant obstacle type
		//if the tool is singleUse make sure to remove it from the seeker
		void apply(Obstacle* currentObstacle);

		string name;
		string relevantObstacle;
    int energySaved;
		bool singleUse;
    int price;
    int quantity;

	void display();
};


////options for configuring the board////
class ResourcesOptions {
public:
	ResourcesOptions(GameManager* gameManager);
	vector<Tool> theResources;
	vector<Obstacle> theObstacles;
    	void displayResources(); 
    	void displayObstacles();
	void eraseResources();
	void eraseObstacles();
	
private:
	GameManager* gameMgr;
};


class Resources {
  public:
    //constructor
    Resources(GameManager* gameManager, const ResourcesOptions& resourcesOptions);
    void displayResources(); 
    void displayObstacles();
    vector<Tool> resources;
    vector<Obstacle> obstacles;

  private:
	  GameManager* gameMgr;
};


#endif


