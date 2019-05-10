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
class Obstacle{
	public:

	string name;
	int energyCost;
	char symbol;
	bool removable;

	Obstacle(string obstacleName, int cost, char mapSymbol, bool isRemovable);

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

private:
	GameManager* gameMgr;
};


class Resources {
  public:
    //constructor
    Resources(GameManager* gameManager, const ResourcesOptions& resourcesOptions);
    void displayResources(); 
    vector<Tool> resources;

  private:
	  GameManager* gameMgr;
};


#endif


