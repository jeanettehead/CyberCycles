#include <osgViewer/Viewer>
#include "states.h"

//Creating the viewer	
osgViewer::Viewer viewer;

state current_state = MENU;

//===== code to build main menu =====

//===== end code to build main menu =====

int main()
{
	viewer.realize();
	while(!viewer.done())
	{
	}
	return 0;
}
