/**
* class that that takes care of the keyboard
* input in the game
*/

#include "GameKeyboardHandler.h"
#include <iostream> //fordebuging purposes

using namespace std;
using namespace osg;

GameKeyboardHandler::GameKeyboardHandler(StateManager* state, ControlledCycle* player)
{
	sm = state;
	cc = player;
}

bool GameKeyboardHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	//this will need to be changed
	if(ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
	{
		if(ea.getKey() == 'w')
		{
			cc->setCyclePosition(Vec3(1.0 * cos(cc->rotation), 0, 1.0 * sin(cc->rotation)) + cc->getPosition());
			cc->setCameraPosition(sm->gameCam);

		}
	}
	return true;
}