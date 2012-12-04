#include "ControlledCycle.h"
#include <osgDB/ReadFile> 

ControlledCycle::ControlledCycle()
{
	transformNode = new osg::PositionAttitudeTransform();
	transformNode->setPosition(osg::Vec3(0,0,0));
	transformNode->setAttitude(osg::Quat(M_PI, osg::Vec3(1,0,0)));
	cycle = osgDB::readNodeFile("../assets/Light Cycle/HQ_Movie cycle.obj");
	
	transformNode->addChild(cycle);
}

ref_ptr<Node> ControlledCycle::getNode()
{
	return transformNode;
}

Vec3 ControlledCycle::getPosition()
{
	return transformNode->getPosition();
}
