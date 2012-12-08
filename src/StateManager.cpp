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
#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>

#include <osgText/Font>
#include <osgText/Text>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Projection>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osgGA/TrackballManipulator>



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

void StateManager::enterMenu(ref_ptr<Group> root, ref_ptr<osgViewer::Viewer> viewer)
{
	menuRoot = root;
	menuViewer = viewer;
	
	//makes menu adds it to the graph
	MainMenu* mm = new MainMenu();
	//mainMenuNode = mm->getMenuNode();
	//root->addChild(mainMenuNode);
	
	//adds the keyboard listener to the graph
	MainMenuKeyboardHandler* mmkb = new MainMenuKeyboardHandler(this);
	viewer->addEventHandler(mmkb);
	
	//===== camera code chunk =====
	if(cam == NULL)
	{
		cam = new Camera;
		viewer->setCamera(cam);
	}

    //set up matrix stuff for main menu

       // Projection node for defining view frustrum for menu:
        menuProjectionMatrix = new  Projection;

	// Initialize the projection matrix for viewing everything we
       // will add as descendants of this node.  Positions described 
        //under this node will equate to pixel coordinates.
       menuProjectionMatrix->setMatrix(Matrix::ortho2D(0,1024,0,768));
        // For the menu model view matrix use an identity matrix:
        MatrixTransform* menuModelViewMatrix = new  MatrixTransform;
       menuModelViewMatrix->setMatrix(Matrix::identity());
       // Make sure the model view matrix is not affected by any transforms
       // above it in the scene graph:
       menuModelViewMatrix->setReferenceFrame(Transform::ABSOLUTE_RF);
       // Add the menu projection matrix as a child of the root node
       // Anything under this node will be viewed in 2d
       root->addChild(menuProjectionMatrix);
       menuProjectionMatrix->addChild(menuModelViewMatrix);

    // Add the Geometry node to contain menu geometry as a child of the
       // menu model view matrix.
       mainMenuNode = mm->getMenuNode();
       menuModelViewMatrix->addChild(mainMenuNode);
   
}

void StateManager::exitMenu()
{
	menuRoot->removeChild(menuProjectionMatrix);
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
	
	//keyboard listener
	GameKeyboardHandler* gkb = new GameKeyboardHandler(this, gameObj->getPlayer());
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
