/**
* This class handles switching from one state to another
*/
#include "StateManager.h"
#include "mainmenu.h"
#include "MainMenuKeyboardHandler.h"
#include <iostream> //for debuging

using namespace std; //for debuging
using namespace osg;

StateManager::StateManager()
{
	currentState = MENU;
}

void StateManager::enterMenu(osg::ref_ptr<osg::Group> root, ref_ptr<osgViewer::Viewer> viewer)
{
	//makes menu adds it to the graph
	MainMenu* mm = new MainMenu();
	root->addChild(mm->getMenuNode());
	
	//adds the keyboard listener to the graph
	MainMenuKeyboardHandler* mmkb = new MainMenuKeyboardHandler();
	viewer->addEventHandler(mmkb);
	
	//===== camera code chunk =====
	mainMenuCam = new osg::Camera;
	
	//background color
	mainMenuCam->setClearColor(osg::Vec4(0, 0, 255, 1));
 	
 	// set dimensions of the view volume
	mainMenuCam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
	mainMenuCam->setViewMatrixAsLookAt(
		osg::Vec3(-7.5, 7.5, 0),// location
		osg::Vec3(0, 0, 0),	// gaze at
		osg::Vec3(0, 1, 0));	// up vector
	
	viewer->setCamera(mainMenuCam);
	//===== end camera code chunk
}
