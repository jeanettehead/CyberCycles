/**
* class that that takes care of the keyboard
* input in the game
*/

#include "GameKeyboardHandler.h"
#include <iostream> //fordebuging purposes

using namespace std;
using namespace osg;

GameKeyboardHandler::GameKeyboardHandler(StateManager* state)
{
	sm = state;
}

bool GameKeyboardHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	if(ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
	{
		std::cout << "you pressed a key in the game" << std::endl;
	}
	return true;
}
