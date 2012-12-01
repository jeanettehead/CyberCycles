/**
* This is the header for the class that takes 
* care of the keyboard input for the main menu
*/

#ifndef MAINMENUKB_H
#define MAINMENUKB_H

#include <osgGA/GUIEventHandler>

class MainMenuKeyboardHandler : public osgGA::GUIEventHandler
{
	public:
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
		virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};
#endif
