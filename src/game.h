#ifndef GAME_H
#define GAME_H

#include "CCMap.h"
#include "ControlledCycle.h"
#include <osg/Camera>

using namespace osg;
class CCGame
{
	public:
		CCGame();
		ref_ptr<Group> getGameNode();
		ControlledCycle* getPlayer();
		void setCameraOnPlayer(ref_ptr<Camera> cam);
		
	private:
		ref_ptr<Group> gameNode;
		CCMap* map;
		void loadBuiltInMap();
		ControlledCycle* player;	
};

#endif
