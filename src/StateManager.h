#ifndef STATES_H
#define STATES_H
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/Camera>

using namespace osg;

class StateManager
{
	public:
		enum state
		{
			MENU,
			GAME,
			EXIT
		};
		
		state currentState;		
		StateManager();

		void enterMenu(ref_ptr<Group> root, ref_ptr<osgViewer::Viewer> viewer);
		void exitMenu();
		void enterGame();
		void exitGame();
	
	private:
		//main menu items
		ref_ptr<Node> mainMenuNode;
		ref_ptr<Camera> mainMenuCam;
		//these are the root and view the main menu was attached to
		ref_ptr<Group> menuRoot;
		ref_ptr<osgViewer::Viewer> menuViewer;
};
#endif
