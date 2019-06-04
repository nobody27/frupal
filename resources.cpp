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
				cout << "\nObstacle name: " << name << 
								"\nEnergy cost: " << energyCost  <<
								"\nSymbol: " << symbol <<
								"\nRemovable: ";
				if(removable){
								cout << "Yes";
				}else{
								cout << "No";
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
				Tool weedWacker("WEEDWACKER", "BUSH", 2, false, 2, 1); 
				theResources.push_back(weedWacker);
				/*Tool jackHammer("JACKHAMMER", "ROCK", 2, false, 10, 1);
					theResources.push_back(jackHammer);
					Tool chainSaw("CHAINSAW", "TREE", 2, false, 5, 1);
					theResources.push_back(chainSaw);
				 */
				Tool boat("BOAT", "WATER", 2, false, 20, 1);
				theResources.push_back(boat);
				Tool binoculars("BINOCULARS", "N/A", 2, false, 1, 1);
				theResources.push_back(binoculars);
				Tool powerBar("POWER BAR", "N/A", 3, true, 5, 10);
				theResources.push_back(powerBar);
				/*some hard coded obstacles
					Obstacle ROCK("ROCK", 5, '@', 1);
					theObstacles.push_back(ROCK);  
					Obstacle TREE("TREE", 5, '#', 1);
					theObstacles.push_back(TREE);  
					Obstacle BUSH("BUSH", 5, '*', 1);
					theObstacles.push_back(BUSH);  
					Obstacle WATER("WATER", 1, '~', 0);
					theObstacles.push_back(WATER);  
				 */
}

void ResourcesOptions::displayResources()
{
				int i = 1;
				//note that the price header is moved one char to the left
				//to compensate for the "$" 
				cout << "  " << setw(14) << left << "Tool" 
								<< " " << setw(8) << left << "Price" 
								<< " " << setw(15) << left << "Energy saved"
								<< " " << setw(12) << left << "Quantity" 
								<< " " << setw(15) << left << "Obstacle" 
								<< endl;

				for (auto it = begin(theResources); it != end(theResources); ++it, ++i) 
				{
								cout << i << " " << setw(15) << left << it->name << 
												"$" << setw(7) << left << it->price << 
												" " << setw(15) << left << it->energySaved << 
												" " << setw(12) << left << it->quantity << 
												" " << setw(15) << left << it->relevantObstacle << 
												endl;
				}
				return;
}
void ResourcesOptions::displayObstacles(){
				int i = 1;
				cout << "  " << setw(14) << left << "Obstacle"
								<< " " << setw(15) << left << "Energy cost"
								<< " " << setw(10) << left << "Symbol"
								<< " " << setw(10) << left << "Removable" << endl;
				for(auto it = begin(theObstacles); it != end(theObstacles); ++it, ++i){
								cout << i << " " << setw(15) << left << it->name <<
												" " << setw(14) << left << it->energyCost <<
												" " << setw(10) << left << it->symbol <<
												" " << setw(10) << left;
								if(it->removable){
												cout << "Yes";
								}else{
												cout << "No";
								}
								cout << endl;
				}
}
void ResourcesOptions::printObstacleKey(){
				cout << BOARD_KEY_COLOR << "Obstacle Key:      NO OBSTACLE = 'o'";
				for(auto it = begin(theObstacles); it != end(theObstacles); ++it){
								if(it->name.compare( "WATER")==0)
								{
												cout << BOARD_KEY_COLOR << "    " << it->name << " = " << BLUE << "'" << it->symbol << "'" << RESET;
								}
								else
								{
												cout << BOARD_KEY_COLOR << "    " << it->name << " = " << OBSTACLE_COLOR << "'" << it->symbol << "'" << RESET;
								}
				}
}

void ResourcesOptions::eraseResources(){
				theResources.erase(theResources.begin(), theResources.begin()+theResources.size());
}
void ResourcesOptions::eraseObstacles(){
				theObstacles.erase(theObstacles.begin(), theObstacles.begin()+theObstacles.size());
}

Resources::Resources(GameManager* gameManager, const ResourcesOptions& options) :
				resources(options.theResources),
				obstacles(options.theObstacles),				gameMgr(gameManager)
{}

void Resources::displayResources()
{
				int i = 1;
				//note that the price header is moved one char to the left
				//to compensate for the "$" 
				cout << "  " << setw(14) << left << "Tool" 
								<< " " << setw(8) << left << "Price" 
								<< " " << setw(13) << left << "Energy Saved"
								//		<< " " << setw(15) << left << "Quantity" 
								<< " " << setw(10) << left << "Obstacle" 
                << " " << setw(12) << left << "Single Use"
								<< endl;

				for (auto it = begin(resources); it != end(resources); ++it, ++i) 
				{
								cout << i << " " << setw(15) << left << it->name << 
												"$" << setw(7) << left << it->price << 
												" " << setw(13) << left << it->energySaved << 
												//			" " << setw(15) << left << it->quantity << 
												" " << setw(10) << left << it->relevantObstacle <<
                        " " << setw(12) << left;
                        if(it->singleUse) { 
                          cout << "YES";
                        }
                        else {
                          cout << "NO";
                        }
                        cout << endl;
				}
				return;
}


void Resources::displayObstacles(){
				int i = 1;
				for(auto it = begin(obstacles); it != end(obstacles); ++it, ++i){
								//	it.display();

				}


}
