#ifndef STATES_H
#define STATES_H
#include <osg/Group>
#include <osgViewer/Viewer>

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

		void enterMenu(osg::ref_ptr<osg::Group> root, osgViewer::Viewer viewer);
		void exitMenu();
		void enterGame();
		void exitGame();
};
#endif
