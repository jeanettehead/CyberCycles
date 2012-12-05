#include "game.h"

CCGame::CCGame()
{
	gameNode = new Group();
	
	map = new CCMap();
	map->buildBuiltInWorld();	
	gameNode->addChild(map->getMapNode());
	
	player = new ControlledCycle();
	gameNode->addChild(player->getNode());
	
	
	//lighting stuff
	ref_ptr<LightSource> ls = new LightSource();
	ref_ptr<Light> ambientLight = new Light();
	ambientLight->setAmbient(Vec4d(1.0,1.0,1.0,1.0));
	ls->setLight(ambientLight);
	gameNode->addChild(ls);
}

ref_ptr<Group> CCGame::getGameNode()
{
	return gameNode;
}

ControlledCycle* CCGame::getPlayer()
{
	return player;
}

void CCGame::setCameraOnPlayer(ref_ptr<Camera> cam)
{
	player->setCameraPosition(cam);
}
