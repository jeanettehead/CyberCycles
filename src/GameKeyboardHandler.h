/**
* This is the header for the class that takes 
* care of the keyboard input in the game
*/

#ifndef GAMEKB_H
#define GAMEKB_H

#include <osgGA/GUIEventHandler>
#include "StateManager.h"
#include "ControlledCycle.h"

using namespace osg;
class GameKeyboardHandler : public osgGA::GUIEventHandler
{
	public:
		GameKeyboardHandler(StateManager* state, ControlledCycle* player);
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
		virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
		
	private:
		StateManager* sm;
		ControlledCycle* cc;
};
#endif
