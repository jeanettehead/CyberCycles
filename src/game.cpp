#include "game.h"

CCGame::CCGame()
{
	gameNode = new Group();
	
	map = new CCMap();
	map->buildBuiltInWorld();	
	gameNode->addChild(map->getMapNode());
	
	player = new ControlledCycle();
	gameNode->addChild(player->getNode());
}

ref_ptr<Group> CCGame::getGameNode()
{
	return gameNode;
}

ControlledCycle* CCGame::getPlayer()
{
	return player;
}
