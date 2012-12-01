#include <osgViewer/Viewer>
#include "StateManager.h"
#include "MainMenuKeyboardHandler.h"

//===== code that starts asset loader =====

//===== end code that starts asset loader =====

//===== code to build main menu =====

//===== end code to build main menu =====

int main()
{	
	//Creating the viewer	
	osgViewer::Viewer viewer;
	
	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);
	
	StateManager* sm = new StateManager();
	sm->enterMenu(root, viewer);
	
	viewer.setSceneData(root);
	viewer.realize(); //makes it so the viewer works
	while(!viewer.done())
	{
		viewer.frame();
		viewer.requestRedraw();
	}
	return 0;
}
