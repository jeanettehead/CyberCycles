#ifndef STATES_H
#define STATES_H
#include <osg/Group>
#include <osgViewer/Viewer>

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

		void enterMenu(osg::ref_ptr<osg::Group> root, ref_ptr<osgViewer::Viewer> viewer);
		void exitMenu();
		void enterGame();
		void exitGame();
	
	private:
		ref_ptr<Camera> mainMenuCam;
};
#endif
