/**
* class that that takes care of the keyboard
* input on the main menu
*/

#include "MainMenuKeyboardHandler.h"
#include <iostream> //fordebuging purposes

using namespace std;
using namespace osg;

MainMenuKeyboardHandler::MainMenuKeyboardHandler(StateManager* state)
{
	sm = state;
}
bool MainMenuKeyboardHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	if(ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
	{
		std::cout << "you pressed a key in the main menu" << std::endl;
		if(ea.getKey() == 'e')
		{
			std::cout << "-----> It was e" << std::endl;
			sm->exitMenu();
			sm->enterGame();
		}
	}

	return true;
}
