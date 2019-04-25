#include "resources.h"

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
  Tool weedWacker("weedWacker", "bush", 2, false, 5, 1); 
  theResources.push_back(weedWacker);


}

Resources::Resources(GameManager* gameManager, const ResourcesOptions& options) :
												resources(options.theResources),
												gameMgr(gameManager)
{}



