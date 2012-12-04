#ifndef GAME_H
#define GAME_H

#include "CCMap.h"
#include "ControlledCycle.h"

using namespace osg;
class CCGame
{
	public:
		CCGame();
		ref_ptr<Group> getGameNode();
		ControlledCycle* getPlayer();
		
	private:
		ref_ptr<Group> gameNode;
		CCMap* map;
		void loadBuiltInMap();
		ControlledCycle* player;	
};

#endif
