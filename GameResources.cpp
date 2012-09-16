#include "GameResources.h"

GameResources * GameResources::instance = 0;

GameResources::GameResources(void) : 
	resourceManager("data/resources.xml")
{
	playNode = 0;
}

GameResources::~GameResources(void)
{
}

void GameResources::SetPlayNode(PlayNode *playNode)
{
	this->playNode = playNode;
}

PlayNode & GameResources::GetPlayNode()
{
	return *playNode;
}

CL_ResourceManager & GameResources::GetResourceManager()
{
	return resourceManager;
}
