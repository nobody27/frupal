#include "resources.h"
#include <iomanip>
using namespace std;

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
}

Resources::Resources(GameManager* gameManager, const ResourcesOptions& options) :
												resources(options.theResources),
												gameMgr(gameManager)
{}

void Resources::displayResources()
{
  int i = 1;
  for (auto it = begin(resources); it != end(resources); ++it, ++i) 
  {
    cout << i << " " << setw(13) << left << (*it).name << right << "$" << (*it).price << endl;
  }
  return;
}


