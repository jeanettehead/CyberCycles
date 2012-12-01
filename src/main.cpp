#include <osgViewer/Viewer>
#include "states.h"
#include "MainMenuKeyboardHandler.h"

//Creating the viewer	
osgViewer::Viewer viewer;

state current_state = MENU;

//===== code that starts asset loader =====

//===== end code that starts asset loader =====

//===== code to build main menu =====

//===== end code to build main menu =====

int main()
{
	//test code
	MainMenuKeyboardHandler* test = new MainMenuKeyboardHandler();
	viewer.addEventHandler(test);
	
	viewer.realize();
	while(!viewer.done())
	{
		viewer.frame();
		viewer.requestRedraw();
	}
	return 0;
}
