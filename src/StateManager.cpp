/**
* This class handles switching from one state to another
*/
#include "StateManager.h"
#include "mainmenu.h"
#include "MainMenuKeyboardHandler.h"
#include <iostream> //for debuging

using namespace std; //for debuging

StateManager::StateManager()
{
	currentState = MENU;
}

void StateManager::enterMenu(osg::ref_ptr<osg::Group> root, osgViewer::Viewer viewer)
{
	MainMenu* mm = new MainMenu();
	//add mm to root here
	MainMenuKeyboardHandler* test = new MainMenuKeyboardHandler();
	viewer.addEventHandler(test);
}
