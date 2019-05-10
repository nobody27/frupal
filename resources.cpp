#include "resources.h"
#include <iomanip>
using namespace std;

//Obstacle constructor
Obstacle::Obstacle(string obstacleName, int cost, char mapSymbol, bool isRemovable){
	name = obstacleName;
	energyCost = cost;
	symbol = mapSymbol;
	removable = isRemovable;
}

void Obstacle::display(){
cout << "\nObstacle: " << name << ", costs " << energyCost  <<
	"\nSymbol: " << symbol <<
	"\nRemovable: ";
if(removable){
	cout << "Y";
}else{
	cout << "N";
}

}

//"default" constructor, only name and relevant obstacle provided
Tool::Tool(string theName, string obstacleName) : energySaved(1) ,
singleUse(true) , price(1) , quantity(1)
{
  name = theName;
  relevantObstacle = obstacleName; 
}

//constructor for when options menu passes in all user selected values for tools
Tool::Tool(string theName, string obstacleName, int theEnergySaved, bool
isSingleUse, int thePrice, int theQuantity) : energySaved(theEnergySaved) ,
singleUse(isSingleUse) , price(thePrice) , quantity(theQuantity)
{
  name = theName;
  relevantObstacle = obstacleName;
}

void Tool::display(){
cout << "\nTool: " << name <<
	"\nEffective against: " << relevantObstacle <<
	"\nSaves: " << energySaved << " energy" <<
	"\nPrice: " << price <<
	"\nQuantity: " << quantity;
}


ResourcesOptions::ResourcesOptions(GameManager* gameManager) : 
										gameMgr(gameManager)
{
  //hard coded tools to start and test
  Tool weedWacker("weedWacker", "bush", 2, false, 2, 1); 
  theResources.push_back(weedWacker);
  Tool jackHammer("jackHammer", "rock", 2, false, 10, 1);
  theResources.push_back(jackHammer);
  Tool chainSaw("chainSaw", "forest", 2, false, 5, 1);
  theResources.push_back(chainSaw);
  Tool boat("boat", "water", 2, false, 20, 1);
  theResources.push_back(boat);
  Tool binoculars("binoculars", "none", 2, false, 1, 1);
  theResources.push_back(binoculars);
  Tool powerBar("powerBar", "none", 3, true, 5, 10);
  theResources.push_back(powerBar);
}

Resources::Resources(GameManager* gameManager, const ResourcesOptions& options) :
												resources(options.theResources),
												gameMgr(gameManager)
{}

void Resources::displayResources()
{
  int i = 1;
	//note that the price header is moved one char to the left
	//to compensate for the "$" 
	cout << i << " " << setw(14) << left << "name" 
			<< " " << setw(8) << left << "price" 
			<< " " << setw(15) << left << "energy_saved" 
			<< " " << setw(15) << left << "number_left" 
			<< " " << setw(15) << left << "obstacle" 
			<< endl;

  for (auto it = begin(resources); it != end(resources); ++it, ++i) 
  {
    cout << i << " " << setw(15) << left << it->name << 
			"$" << setw(7) << left << it->price << 
			" " << setw(15) << left << it->energySaved << 
			" " << setw(15) << left << it->quantity << 
			" " << setw(15) << left << it->relevantObstacle << 
			endl;
  }
  return;
}


