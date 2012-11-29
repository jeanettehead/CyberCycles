#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu
{
	osg::ref_ptr<osg::Group> menu_node;
	
	public:	
		MainMenu(osg::ref_ptr<osg::Group> root);
};

#endif
