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
	transFromMenuToGame = false;
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
	if(cam == NULL)
	{
		cam = new Camera;
		viewer->setCamera(cam);
	}
	
	//background color
	cam->setClearColor(osg::Vec4(0, 0, 255, 1));
 	
 	// set dimensions of the view volume
	cam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
	cam->setViewMatrixAsLookAt(
		osg::Vec3(-7.5, 7.5, 0),// location
		osg::Vec3(0, 0, 0),	// gaze at
		osg::Vec3(0, 1, 0));	// up vector
	
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
	
	//game node
	CCGame* gameObj = new CCGame();
	gameNode = gameObj->getGameNode();
	root->addChild(gameNode);
	cout << "after game stuff added" << endl;
	
	//keyboard listener
	GameKeyboardHandler* gkb = new GameKeyboardHandler(this);
	viewer->addEventHandler(gkb);
	
	//===== camera code chunk =====
	if(cam == NULL)
	{
		cam = new Camera;
		viewer->setCamera(cam);
	}
	
	//background color
	cam->setClearColor(osg::Vec4(0, 0, 0, 1));
 	
 	// set dimensions of the view volume
	/*cam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
	cam->setViewMatrixAsLookAt(
		osg::Vec3(0, 7.5, -7.5),// location
		gameObj->getPlayer()->getPosition(),	// gaze at
		osg::Vec3(0, 1, 0));	// up vector
	//===== end camera code chunk ===== */
	
	gameObj->setCameraOnPlayer(cam);
}
