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
	
	/*ref_ptr<LightSource> test = new LightSource();
	ref_ptr<Light> testLight = new Light();
	testLight->setDiffuse(Vec4d(1.0,0.0,0.0,1.0));
	test->setLight(testLight);
	testLight->setPosition(Vec4d(0.0, 5.0, 0.0, 1.0));
	gameNode->addChild(test);*/
	
	//curenlty makes no diferent
	//ref_ptr<StateSet> ss = gameNode->getOrCreateStateSet();
	//ls->setStateSetModes(*ss, StateAttribute::ON);
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
