/**
* This class handles switching from one state to another
*/
#include "StateManager.h"
#include "mainmenu.h"
#include "MainMenuKeyboardHandler.h"
#include "GameKeyboardHandler.h"
#include <osgViewer/View>
#include <iostream>
#include <list>

using namespace std;
using namespace osg;

StateManager::StateManager()
{
	currentState = MENU;
}

void StateManager::removeAllEventHandlers()
{
	(menuViewer->getEventHandlers()).clear();
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
	currentState = GAME;
	
	gameRoot = root;
	gameViewer = viewer;
	
	//need to actually create game node
	
	//need to add keyboard listener
	GameKeyboardHandler* gkb = new GameKeyboardHandler(this);
	viewer->addEventHandler(gkb);
	
	//===== camera code chunk =====
	gameCam = new Camera;
	
	//background color
	gameCam->setClearColor(osg::Vec4(0, 0, 255, 1));
 	
 	// set dimensions of the view volume
	gameCam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
	gameCam->setViewMatrixAsLookAt(
		osg::Vec3(-7.5, 7.5, 0),// location
		osg::Vec3(0, 0, 0),	// gaze at
		osg::Vec3(0, 1, 0));	// up vector
	
	/*if(viewer == NULL)
	{
		cout << "The viewer is null." << endl;
		cout.flush();
		exit(1);
	}
	else
	{
		cout << "The viewer is not null." << endl;
	}*/
	viewer->setCamera(gameCam);
	//===== end camera code chunk ===== */
}
