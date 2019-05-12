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
//	are any of these sill needed ^ ?
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

//Function to clear screen and reset curson
void GameManager::clear_screen(){
	if(SCREEN_CLEARING_ENABLED){	
		cout << "\033[2J\033[1;1H";
	}
}

//Funtion to read data from config file into the appropriate fields
void GameManager::readConfigFile(){
	string fileName = DEFAULT_CONFIG_FILE;	//set in GameManager.h 
	//most of these fields temporarily store values to pass to tool/obstacle constructors
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
	bool confirmed = false;

	cout << "\nReading from file \"" << fileName << "\"." <<
		"\nRead from a different file?" <<
		"\nPress 'Y' to change the file name, " <<
		"or any other key to skip." <<
		"\n\n>";
	cin >> reply;
	reply = toupper(reply);
	if(reply == 'Y'){	//prompt user for and verify new config file name
		while(!confirmed){	//loop until user confirms choice
			cout << "\nEnter the new file name: ";
			cin >> name;
			while(cin.fail()){
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\nInvalid entry. " <<
					"Enter the new file name: ";
				cin >> name;
			}
			cout << "\nYou entered \"" << name <<
				"\". Is this correct? " <<
				"\nPress 'Y' to confirm" <<
				" or any other key to edit." <<
				"\n\n>";
			cin >> reply;
			reply = toupper(reply);
			while(cin.fail() || (reply != 'Y' && reply != 'N')){
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\nInvalid entry. " <<
					"\nPress 'Y' to change the file name, " <<
					"or any other key to skip." <<
					"\n\n>";
				cin >> reply;
				reply = toupper(reply);
			}	
			if(reply == 'Y'){
				confirmed = true;
				fileName = name;
			}
		}
	}

	configFile.open(fileName);
	while(getline(configFile, type, ',')){	//read first digit of each line into type
		if(type[0] == GENERAL_CONFIGURATION){	//general configs are just a variable name and an int
			getline(configFile, name, ',');			//get the name
			getline(configFile, value, '\n');		//get the int
			if(!name.compare("boardSize")){			//determine which setting it is.
				boardOptions->size = stoi(value);	//configure the appropriate setting
			}else if(!name.compare("startEnergy")){		//doing it this way means the lines
				seekerOptions->theEnergy = stoi(value);	//can be read in any order
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
			}else if(!name.compare("binocularCost")){
				//TODO: put this value in the right place
			}
		}else if(type[0] == OBSTACLE_CONFIGURATION){	//obstacle configs contain a value for each
			getline(configFile, obstacleName, ',');	//field contained in the obstacle class
			getline(configFile, value, ',');
			energyCost =stoi(value);
			getline(configFile, value, ',');
			symbol = value[0];
			getline(configFile, value);
			removable = stoi(value);
			//after getting the values, create an obstacle and push it to the vector
			Obstacle newObstacle(obstacleName, energyCost, symbol, removable);
			resourcesOptions->theObstacles.push_back(newObstacle);
		}else if(type[0] == TOOL_CONFIGURATION){	//tool configs contain a value for each
			getline(configFile, toolName, ',');	//field contained in the tool class
			getline(configFile, obstacleName, ',');
			getline(configFile, value, ',');
			energySaved = stoi(value);
			getline(configFile, value, ',');
			singleUse = stoi(value);
			getline(configFile, value, ',');
			price = stoi(value);
			getline(configFile, value);
			quantity = stoi(value);
			//after getting the values, create a tool and push it to the vector	
			Tool newTool(toolName, obstacleName, energySaved, singleUse, price, quantity);
			resourcesOptions->theResources.push_back(newTool);
		}
	}
}

//
void GameManager::writeConfigFile(){
	ofstream configFile;
	string fileName = DEFAULT_CONFIG_OUTPUT;
	string name;
	char reply = ' ';
	bool confirmed = false;
	int i = 1;
	int j = 1;

	clear_screen();

	cout << "\nWriting to file \"" << fileName << "\"." <<
		"\nWrite to a different file?" <<
		"\nPress 'Y' to change the file name, " <<
		"or any other key to skip." <<
		"\n\n>";
	cin >> reply;
	reply = toupper(reply);
	if(reply == 'Y'){		//prompt user for and verify new config file name
		while(!confirmed){	//loop until user confirms choice
			cout << "\nEnter the new file name: ";
			cin >> name;
			while(cin.fail()){
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\nInvalid entry. " <<
					"Enter the new file name: ";
				cin >> name;
			}
			cout << "\nYou entered \"" << name <<
				"\". Is this correct? " <<
				"\nPress 'Y' to confirm" <<
				" or any other key to edit." <<
				"\n\n>";
			cin >> reply;
			reply = toupper(reply);
			while(cin.fail() || (reply != 'Y' && reply != 'N')){
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\nInvalid entry. " <<
					"\nPress 'Y' to change the file name, " <<
					"or any other key to skip." <<
					"\n\n>";
				cin >> reply;
				reply = toupper(reply);
			}	
			if(reply == 'Y'){
				confirmed = true;
				fileName = name;
			}
		}
	}

	configFile.open(fileName);	//print out the integers first
	configFile << GENERAL_CONFIGURATION << ",boardSize," << boardOptions->size << "\n"
		<< GENERAL_CONFIGURATION << ",startEnergy," << seekerOptions->theEnergy << "\n"
		<< GENERAL_CONFIGURATION << ",startMoney," << seekerOptions->theMoney << "\n"
		<< GENERAL_CONFIGURATION << ",startX," << seekerOptions->x << "\n" 
		<< GENERAL_CONFIGURATION << ",startY," << seekerOptions->y << "\n"
		<< GENERAL_CONFIGURATION << ",hasBoat," << seekerOptions->hasBoat << "\n"
		<< GENERAL_CONFIGURATION << ",hasBinoculars," << seekerOptions->hasBinoculars << "\n";
	//now iterate through the obstacle vector and print out the data in the right format.
	for(auto it = begin(resourcesOptions->theObstacles); it != end(resourcesOptions->theObstacles); ++it, ++i){
		configFile << OBSTACLE_CONFIGURATION << "," 
			<< it->name << ","
			<< it->energyCost << ","
			<< it->symbol << ","
			<< it->removable << "\n";
	}
	//now iterate through the tool vector and print out the data in the right format.
	for(auto it = begin(resourcesOptions->theResources); it != end(resourcesOptions->theResources); ++it, ++j){
		configFile << TOOL_CONFIGURATION << "," 
			<< it->name << ","
			<< it->relevantObstacle << ","
			<< it->energySaved << ","
			<< it->price << ","
			<< it->quantity << "\n";
	}

	configFile.close();
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
