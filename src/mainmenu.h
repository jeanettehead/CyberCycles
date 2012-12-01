#ifndef MAINMENU_H
#define MAINMENU_H

#include <osgViewer/Viewer>
#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/ShapeDrawable>

using namespace osg;
class MainMenu
{
	ref_ptr<Group> menu_node;
	
	public:	
		MainMenu();
		ref_ptr<Node> getMenuNode();
};

#endif
