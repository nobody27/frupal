/////////////////////////////////////////////////////
// CS300 
// Winter 2019
// A - Team: Jessica, Elyse, Max, John, Leior
// The Island of Frupal
/////////////////////////////////////////////////////

//include local headers
#include "GameManager.h"
#include "OptionsMenu.h"
#include "seeker.h"
#include "boardNtile.h"

//include libraries
#include <iostream>
#include <iomanip>

#define GRAY "\033[90m"
#define RESET "\033[0m"
using namespace std;

OptionsMenu::OptionsMenu(GameManager* gameManager) : gameMgr(gameManager), quit(false){
	//sub-menu default constructors should be enough
}

void OptionsMenu::clear_screen(){
	cout << "\n033[2J\033[1;1H";
}

//we might be shooting ourselves in the foot implementing a non-essential feature
//but what the heck, why not :)
//done - indicates that we are done with this menu and we should return to the main menu
//quit - indicates that we are performing a quick quit to exit the game immediately
bool OptionsMenu::call() {
	bool done = false;
	quit = false;

	while (!done && !quit) {
		done = getAndExecuteCommand();
	}
	return quit;
}

void OptionsMenu::display() const {
	//print the options
	//system("clear");
	cout << "Make Your Choice: " << endl;
	if(gameMgr->initialized) {
		cout << GRAY;
	}
	//// Place text for options that are not available after initialization here ////
	cout << setw(15) << left << "(S) set board size" << endl;
	cout << setw(15) << left << "(E) set seeker's initial energy level" << endl;
	cout << setw(15) << left << "(M) set seeker's initial money" << endl;
	cout << setw(15) << left << "(T) configure tools" << endl;
	cout << setw(15) << left << "(O) configure obstacles" << endl;
	/////////////////////////////////////////////////////////////////////////////////
	if(gameMgr->initialized) {
		cout << RESET;
	}
	cout << setw(15) << left << "(R)eturn to the Main Menu" << endl;
	cout << setw(15) << left << "(Q)uit the program" << endl;
	cout << "\n\n\n";
	//TODO load, save
}

bool OptionsMenu::getAndExecuteCommand() {
	bool done = false;
	bool again = true;
	bool unsupportedAfterInitialization = false;

	while(again) {
		again = false;
		unsupportedAfterInitialization = false;
		char choice = 0;
		//display the menu options
		display();
		//request the command
		cin >> choice;
		//capitalize and check for legal input

		//TODO all the code regarding initialized should be moved to methods
		// in order to avoid code duplication
		switch (toupper(choice)) {
			case 'S':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setBoardSize(); //try again if command fails
				}
				break;
			case 'E':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setSeekerEnergy(); //try again if command fails
				}
				break;
			case 'M':
				if(gameMgr->initialized) {
					unsupportedAfterInitialization = true;
				} else {
					again = !setSeekerMoney(); //try again if command fails
				}
				break;
			case 'T':
				if(gameMgr->initialized){
					unsupportedAfterInitialization = true;
				}else{
					again = !configureTools();
				}
				break;
			case 'O':
				if(gameMgr->initialized){
					unsupportedAfterInitialization = true;
				}else{
					again = !configureObstacles();
				}
				break;
				//TODO other options
			case 'R':
				cout << "returning to main menu" << endl;
				done = true;
				break;
			case 'Q':
				//exit - quick quit 
				cout << "quitting the game" << endl;
				done = true;
				quit = true;
				break;
			default:
				cout << "'" << choice <<  "' is not a valid command in the game menu..." << endl;
				again = true;
		}
		if(unsupportedAfterInitialization) {
			cout << "'" << choice << "' is not valid after the game has begun..." << endl;
			again = true;
		}
	}
	return done;
}

//TODO create utility method that does the repetative work
bool OptionsMenu::setBoardSize() {
	bool fail = false;
	size_t size = 0;
	size_t min = 2;
	size_t max = 20;
	cout << "Please enter desired board size in the range [ " << 
		min << ".." << max << "]" << endl;
	//TODO error handling and check for good range
	cin >> size; 
	if(cin.fail()) {
		fail = true;
		cin.clear();
		cin.ignore(100, '\n');
	}
	if (fail || size < min || size > max) {
		cout << "invalid size -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->boardOptions->size=size;
	return true; //success
}

bool OptionsMenu::setSeekerEnergy() {
	bool fail = false;
	size_t energy = 0;
	size_t min = 1;
	size_t max = 99;
	cout << "Please enter how much energy the seeker will start with in the range [" << 
		min << ".." << max << "]" << endl;
	//TODO error handling and check for good range
	cin >> energy; 
	if(cin.fail()) {
		fail = true;
		cin.clear();
		cin.ignore(100, '\n');
	}
	if (fail || energy < min || energy > max) {
		cout << "invalid energy -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions->theEnergy=energy;
	return true; //success
}

bool OptionsMenu::setSeekerMoney() {
	bool fail = false;
	size_t money = 0;
	size_t min = 0;
	size_t max = 99;
	cout << "Please enter how much money the seeker will start with in the range [" <<
		min << ".." << max << "]" << endl;
	//TODO error handling and check for good range
	cin >> money; 
	if(cin.fail()) {
		fail = true;
		cin.clear();
		cin.ignore(100, '\n');
	}
	if (fail || money < min || money > max) {
		cout << "invalid money -- aborting command" << endl; 
		return false; //failure
	}
	gameMgr->seekerOptions->theMoney=money;
	return true; //success
}

bool OptionsMenu::configureTools(){
	char reply = ' ';
	int toolNum = 0;
	int min = 1;
	int toolCount;	

	while(reply != 'R'){
		toolCount = gameMgr->resourcesOptions->theResources.size();
		if(toolCount < 1){
			cout << "\nThere are currently no tools.";
			cout << "\n(1) Add a new tool";
		}
		if(toolCount > 0){
			cout << "\nCurrent list of tools:" << endl;
			gameMgr->resourcesOptions->displayResources();
			cout << "\n(1) Add a new tool";
			cout << "\n(2) Remove a tool" <<
				"\n(3) Modify a tool";
		}

		cout << "\n(R)eturn to options menu"
			"\nYour choice: ";

		cin >> reply;
		reply = toupper(reply);

		switch(reply){
			case '1':
				addTool();
				break;
			case '2':
				removeTool();
				break;
			case '3':
				toolCount = gameMgr->resourcesOptions->theResources.size();
				if(toolCount == 1){
					modifyTool(1);
				}else{
					cout << "\nWhich tool would you like to modify?" <<
						"\nTool #: ";

					cin >> toolNum;
					while(cin.fail() || toolNum < min || toolNum > toolCount) {
						cin.clear();
						cin.ignore(100, '\n');
						cout << "\nInvalid response. Please enter a number between " << min << " and " << toolCount;
						cout << "\nWhich tool would you like to modify?" <<
							"\nTool #: ";

						cin >> toolNum;
					}
					modifyTool(toolNum);	
					toolNum = 0;
				}
				break;
			default:
				break;
		}
	}
	return true;
}
void OptionsMenu::addTool(){
	string name = "NEW TOOL";
	string obstacle = "OBSTACLE";
	int energySaved = 0;
	bool singleUse = 0;
	int price = 0;
	int quantity = 0;
	int index = gameMgr->resourcesOptions->theResources.size();
	Tool newTool(name, obstacle, energySaved, singleUse, price, quantity);
	gameMgr->resourcesOptions->theResources.push_back(newTool);	
	modifyTool(index+1);
}
void OptionsMenu::removeTool(){

	int reply;
	int min = 1;
	int max = gameMgr->resourcesOptions->theResources.size();
	if(max == 1){
		gameMgr->resourcesOptions->theResources.erase(gameMgr->resourcesOptions->theResources.begin());
	}else{
		cout << "\nEnter the number of the tool you want to remove: ";
		cin >> reply;
		while(cin.fail() || reply < min || reply > max) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid response. Please enter a number between " << min << " and " << max;
			cout << "\nEnter the number of the tool you want to remove: ";
			cin >> reply;
		}
		gameMgr->resourcesOptions->theResources.erase(gameMgr->resourcesOptions->theResources.begin()+reply-1);
	}
}

void OptionsMenu::modifyTool(int toolNumber){
	char reply = ' ';
	string input;
	int value;
	Tool copy = gameMgr->resourcesOptions->theResources[toolNumber-1];

	while(reply != 'R'){
		copy.display();
		cout << "\n\nWhat would you like to change?" <<
			"\n(1) Tool name" <<
			"\n(2) Effective obstacle" <<
			"\n(3) Energy saved" <<
			"\n(4) Price" <<
			"\n(5) Quantity" << 
			"\n(R)eturn to list of tools" << 
			"\nYour Choice: ";

		cin >> reply;
		reply = toupper(reply);
		switch(reply){

			case '1':
				cout << "\nEnter a new name: ";
				cin >> input;
				while(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a new name: ";
					cin >> input;
				}
				cout << "\nChanging the name of \"" << copy.name;
				copy.name = input;
				cout << "\" to \"" << copy.name << "\"";
				break;
			case '2':
				cout << "\nEnter an obstacle name (MUST MATCH OBSTACLE): ";
				cin >> input;
				while(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter an obstacle name (MUST MATCH OBSTACLE): ";
					cin >> input;
				}
				cout << "\nChanging the effective obstacle of \"" <<
					copy.name << "\" from \"" << copy.relevantObstacle;
				copy.relevantObstacle = input;
				cout << "\" to \"" << copy.relevantObstacle << "\"";
				break;
			case '3':
				cout << "\nEnter an amount: ";
				cin >> value;
				while(cin.fail() || value < 0){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a positive number: ";
					cin >> value;
				}
				cout << "\nChanging the energy savings of \"" << 
					copy.name << "\" from " << copy.energySaved;
				copy.energySaved = value;
				cout << " to " << copy.energySaved;	
				break;
			case '4':
				cout << "\nEnter an amount: ";
				cin >> value;
				while(cin.fail() || value < 0){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a positive number: ";
					cin >> value;
				}
				cout << "\nChanging the price of \"" << 
					copy.name << "\" from " << copy.price;
				copy.price = value;
				cout << " to " << copy.price;	
				break;
			case '5':
				cout << "\nEnter an amount: ";
				cin >> value;
				while(cin.fail() || value < 0){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a positive number: ";
					cin >> value;
				}
				cout << "\nChanging the quantity of \"" << 
					copy.name << "\" from " << copy.quantity;
				copy.quantity = value;
				cout << " to " << copy.quantity;	
				break;
			default:
				break;
		}
	}
	gameMgr->resourcesOptions->theResources[toolNumber-1].name = copy.name;
	gameMgr->resourcesOptions->theResources[toolNumber-1].relevantObstacle = copy.relevantObstacle;
	gameMgr->resourcesOptions->theResources[toolNumber-1].energySaved = copy.energySaved;
	gameMgr->resourcesOptions->theResources[toolNumber-1].price = copy.price;
	gameMgr->resourcesOptions->theResources[toolNumber-1].quantity = copy.quantity;

}


bool OptionsMenu::configureObstacles(){
	char reply = ' ';
	int obstacleNum = 0;
	int min = 1;
	int obstacleCount;

	while(reply != 'R'){
		obstacleCount = gameMgr->resourcesOptions->theObstacles.size();

		if(obstacleCount < 1){
			cout << "\nThere are currently no obstacles.";
			cout << "\n(1) Add a new obstacle";
		}else if(obstacleCount > 0){
			cout << "\nCurrent list of obstacles:" << endl;
			gameMgr->resourcesOptions->displayObstacles();
			cout << "\n(1) Add a new obstacle" <<
				"\n(2) Remove an obstacle" <<
				"\n(3) Modify an obstacle";
		}

		cout << "\n(R)eturn to options menu"
			"\nYour choice: ";

		cin >> reply;
		reply = toupper(reply);

		switch(reply){
			case '1':
				addObstacle();
				break;
			case '2':
				removeObstacle();
				break;
			case '3':
				obstacleCount = gameMgr->resourcesOptions->theObstacles.size();
				if(obstacleCount == 1){
					modifyObstacle(1);
				}else{
					cout << "\nWhich obstacle would you like to modify?" <<
						"\nObstacle #: ";

					cin >> obstacleNum;
					while(cin.fail() || obstacleNum < min || obstacleNum > obstacleCount) {
						cin.clear();
						cin.ignore(100, '\n');
						cout << "\nInvalid response. Please enter a number between " << min << " and " << obstacleCount;
						cout << "\nWhich obstacle would you like to modify?" <<
							"\nObstacle #: ";

						cin >> obstacleNum;
					}
					modifyObstacle(obstacleNum);	
					obstacleNum = 0;
				}
				break;
			default:
				break;
		}
	}
	return true;
}
void OptionsMenu::addObstacle(){
	string name = "NEW OBSTACLE";
	int energyCost = 0;
	char symbol = '!';
	bool removable = 1;
	int index = gameMgr->resourcesOptions->theObstacles.size();
	Obstacle newObstacle(name, energyCost, symbol, removable);
	gameMgr->resourcesOptions->theObstacles.push_back(newObstacle);
	modifyObstacle(index+1);
}
void OptionsMenu::removeObstacle(){
	int reply;
	int min = 1;
	int max = gameMgr->resourcesOptions->theObstacles.size();
	if(max == 1){
		gameMgr->resourcesOptions->theObstacles.erase(gameMgr->resourcesOptions->theObstacles.begin());
	}else{
		cout << "\nEnter the number of the obstacle you want to remove: ";
		cin >> reply;
		while(cin.fail() || reply < min || reply > max) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid response. Please enter a number between " << min << " and " << max;
			cout << "\nEnter the number of the Obstacle you want to remove: ";
			cin >> reply;
		}
		gameMgr->resourcesOptions->theObstacles.erase(gameMgr->resourcesOptions->theObstacles.begin()+reply-1);
	}
}
void OptionsMenu::modifyObstacle(int obstacleNum){
	char reply = ' ';
	string input;
	int value;
	Obstacle copy = gameMgr->resourcesOptions->theObstacles[obstacleNum-1];

	while(reply != 'R'){
		copy.display();
		cout << "\n\nWhat would you like to change?" <<
			"\n(1) Obstacle name" <<
			"\n(2) Energy cost" <<
			"\n(3) Symbol" <<
			"\n(4) Removability" <<
			"\n(R)eturn to list of obstacles" << 
			"\nYour Choice: ";

		cin >> reply;
		reply = toupper(reply);
		switch(reply){

			case '1':
				cout << "\nEnter a new name: ";
				cin >> input;
				while(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a new name: ";
					cin >> input;
				}
				cout << "\nChanging the name of \"" << copy.name;
				copy.name = input;
				cout << "\" to \"" << copy.name << "\"";
				break;
			case '2':
				cout << "\nEnter an amount: ";
				cin >> value;
				while(cin.fail() || value < 0){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a positive number: ";
					cin >> value;
				}
				cout << "\nChanging the energy cose of \"" << 
					copy.name << "\" from " << copy.energyCost;
				copy.energyCost = value;
				cout << " to " << copy.energyCost;	
				break;
			case '3':
				cout << "\nEnter a new symbol: ";
				cin >> input;
				while(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter a new symbol: ";
					cin >> value;
				}
				cout << "\nChanging the symbol for \"" << 
					copy.name << "\" from '" << copy.symbol;
				copy.symbol = input[0];
				cout << "' to " << copy.symbol;	
				break;
			case '4':
				cout << "\nEnter 1 for removable or 0 for non-removable: ";
				cin >> value;
				while(cin.fail() || value < 0 || value > 1){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid Entry. Enter 1 for removable or 0 for non-removable: ";
					cin >> value;
				}
				cout << "\nChanging the removability of \"" << 
					copy.name << "\" from " << copy.removable;
				copy.removable = value;
				cout << " to " << copy.removable;	
				break;
			default:
				break;
		}
	}
	gameMgr->resourcesOptions->theObstacles[obstacleNum-1].name = copy.name;
	gameMgr->resourcesOptions->theObstacles[obstacleNum-1].energyCost = copy.energyCost;
	gameMgr->resourcesOptions->theObstacles[obstacleNum-1].symbol = copy.symbol;
	gameMgr->resourcesOptions->theObstacles[obstacleNum-1].removable = copy.removable;
}
