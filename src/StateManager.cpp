/**
* This class handles switching from one state to another
*/
#include "StateManager.h"
#include "mainmenu.h"
#include "MainMenuKeyboardHandler.h"
#include <osgViewer/View>
#include <iostream>
#include <list>

using namespace std;
using namespace osg;

StateManager::StateManager()
{
	currentState = MENU;
}

/**
* This method was copied from the internet
* apperently osg does not provide its own method to do this
*/
void StateManager::removeAllEventHandlers()
{
	//note that the white space in the following line are required to make it work
	list<ref_ptr<osgGA::GUIEventHandler>, allocator<ref_ptr<osgGA::GUIEventHandler> > > test;
	test = menuViewer->getEventHandlers();
	if(test.empty())
	{
		cout << "The EventHandler list is empty." << endl;
	}
	else
	{
		test.clear();
	}
}

void StateManager::enterMenu(osg::ref_ptr<osg::Group> root, ref_ptr<osgViewer::Viewer> viewer)
{
	menuRoot = root;
	menuViewer = viewer;
	
	//makes menu adds it to the graph
	MainMenu* mm = new MainMenu();
	mainMenuNode = mm->getMenuNode();
	root->addChild(mainMenuNode);
	
	//adds the keyboard listener to the graph
	MainMenuKeyboardHandler* mmkb = new MainMenuKeyboardHandler(this);
	viewer->addEventHandler(mmkb);
	
	//===== camera code chunk =====
	mainMenuCam = new Camera;
	
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

void StateManager::exitMenu()
{
	menuRoot->removeChild(mainMenuNode);
	removeAllEventHandlers();	
}

/**
* use to use the same root and viewer that
* was set for the main menu if any
*/
void StateManager::enterGame()
{
	if(menuRoot == NULL)
	{
		cerr << "The root var is null." <<endl;
		exit(1);
	}
	if(menuViewer == NULL)
	{
		cerr << "The viewer var is null." <<endl;
		exit(1);
	}
	
	enterGame(menuRoot, menuViewer);
}

void StateManager::enterGame(osg::ref_ptr<osg::Group> root, ref_ptr<osgViewer::Viewer> viewer)
{
	gameRoot = root;
	gameViewer = viewer;
	
	//need to actually create game node
	
	//need to add keyboard listener
	
	//===== camera code chunk =====
	mainMenuCam = new Camera;
	
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
