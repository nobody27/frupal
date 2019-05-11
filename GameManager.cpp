/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//GameInterFace.cpp -- implementationof the global game mananger

#include "GameManager.h"
#include "boardNtile.h" 		//owned by Jessica
								//TODO in the future we may want to separate 
								//board and tile to separate files
#include "seeker.h"				//owned by John
//#include "configurations.h"		//owned by Max
//#include "tools.h"				//owned by John (maybe help from Leior)
//#include "obstacles.h"			//TBD (maybe John or Leior)
#include <assert.h>
#include <iostream>
#include "resources.h"

//constructor
GameManager::GameManager() : theIsland(nullptr), theSeeker(nullptr),
theResources(nullptr) ,   initialized(false) 
{
	//TODO configure at least on terrain or arrange for a default terrain

	mainMenu = new MainMenu(this);
	boardOptions = new BoardOptions(this);
  resourcesOptions = new ResourcesOptions(this);
	seekerOptions = new SeekerOptions(this);

	readConfigFile();
}

//destructor
GameManager::~GameManager() {
	delete theIsland;
	delete theSeeker;
	delete mainMenu;
	delete boardOptions;
	delete seekerOptions;
 // delete resourcesOptions;
}

void GameManager::readConfigFile(){
	string fileName = DEFAULT_CONFIG_FILE;	
	ifstream configFile;
	string type;
	string name;
	string value;
	string toolName;
	string obstacleName;
	int energySaved;
	int singleUse;
	int price;
	int quantity;
	int energyCost;
	char symbol;
	bool removable;

	char reply = ' ';

	cout << "\nReading from file \"" << fileName << "\"." <<
		"\nRead from a different file?" <<
		"\n(Y)es or (N)o: ";
	cin >> reply;
	reply = toupper(reply);
	if(reply == 'Y'){
		cout << "\nEnter the new file name: ";
		cout << "\n(Custom config file name not yet implemented! Using default anyway.)";
	//	cin.getline(fileName);
	}

	configFile.open(fileName);
	while(getline(configFile, type, ',')){
		if(type[0] == '1'){
			getline(configFile, name, ',');
			getline(configFile, value, '\n');
			if(!name.compare("boardSize")){
				boardOptions->size = stoi(value);
			}else if(!name.compare("startEnergy")){
				seekerOptions->theEnergy = stoi(value);
			}else if(!name.compare("startMoney")){
				seekerOptions->theMoney = stoi(value);
			}else if(!name.compare("startX")){
				seekerOptions->x = stoi(value);
			}else if(!name.compare("startY")){
				seekerOptions->y = stoi(value);
			}else if(!name.compare("hasBoat")){
				seekerOptions->hasBoat = stoi(value);
			}else if(!name.compare("hasBinoculars")){
				seekerOptions->hasBinoculars = stoi(value);
			}else if(!name.compare("binocularCose")){
//TODO: put this value in the right place
			}
		}else if(type[0] == '2'){
			getline(configFile, obstacleName, ',');
			getline(configFile, value, ',');
			energyCost =stoi(value);
			getline(configFile, value, ',');
			symbol = value[0];
			getline(configFile, value);
			removable = stoi(value);

			Obstacle newObstacle(obstacleName, energyCost, symbol, removable);
			resourcesOptions->theObstacles.push_back(newObstacle);
		}else if(type[0] == '3'){
			getline(configFile, toolName, ',');
			getline(configFile, obstacleName, ',');
			getline(configFile, value, ',');
			energySaved = stoi(value);
			getline(configFile, value, ',');
			singleUse = stoi(value);
			getline(configFile, value, ',');
			price = stoi(value);
			getline(configFile, value);
			quantity = stoi(value);
		
			Tool newTool(toolName, obstacleName, energySaved, singleUse, price, quantity);
			resourcesOptions->theResources.push_back(newTool);
		}
	}
}

void GameManager::initializeGame() {
	assert(!initialized);
	theIsland = new Board(this, *boardOptions);
  theResources = new Resources(this, *resourcesOptions);
	theSeeker = new Seeker(this, *seekerOptions);
	initialized = true;
	//print introduction
	system("clear");
    cout << endl << endl << "*****************************" << endl;
    cout << "You have landed on Frupal Island!" << endl;
    cout << "As you explore, you will uncover treasure as well as tools to help you on your quest." << endl;
    cout << "Use caution! Moving around the island consumes energy. When you run out of energy, the game will end.";
    cout << endl << "*****************************" << endl;
	cout << "\n\n\n";
	cout << "press ENTER to continue";
	cin.get();
}
