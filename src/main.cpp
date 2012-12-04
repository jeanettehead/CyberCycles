#include <osgViewer/Viewer>
#include "StateManager.h"
#include "MainMenuKeyboardHandler.h"

using namespace osg;

//===== code that starts asset loader =====

//===== end code that starts asset loader =====

//===== code to build main menu =====

//===== end code to build main menu =====

int main()
{	
	//Creating the viewer	
	ref_ptr<osgViewer::Viewer> viewer (new osgViewer::Viewer);
	
	//Creating the root node
	ref_ptr<Group> root (new Group);
	
	StateManager* sm = new StateManager();
	sm->enterMenu(root, viewer);
	
	viewer->setSceneData(root);
	viewer->realize(); //makes it so the viewer works
	while(!viewer->done())
	{
		if(sm->transFromMenuToGame == true)
		{
			sm->exitMenu();
			sm->enterGame();
			sm->transFromMenuToGame = false;
		}
		viewer->frame();
		viewer->requestRedraw();
	}
	return 0;
}
