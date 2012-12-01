/**
* class that that takes care of the keyboard
* input on the main menu
*/

#include "MainMenuKeyboardHandler.h"
#include <iostream> //fordebuging purposes

using namespace std; //cause c++ is stupid

bool MainMenuKeyboardHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	//for debuging
	std::cout << "you pressed a key in the main menu" << std::endl;

	return true;
}
