#include "ControlledCycle.h"
#include <osgDB/ReadFile> 
#include <osg/Quat>
#include <math.h>

#define _USE_MATH_DEFINES

ControlledCycle::ControlledCycle()
{
	cycle = new Group();
	
	rotation = M_PI/2.0f;

	transformNode = new PositionAttitudeTransform();
	transformNode->setPosition(Vec3(0,0,0));
	transformNode->setAttitude(Quat(M_PI, Vec3d(1.0,0.0,0.0), rotation,Vec3d(0.0,-1.0,0.0), 0.0, Vec3d(0.0,0.0,0.0)));
	model = osgDB::readNodeFile("../assets/Light Cycle/HQ_Movie cycle.obj");
	
	cycle->addChild(model);
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

void ControlledCycle::setCameraPosition(ref_ptr<Camera> cam)
{
	Vec3 location = transformNode->getPosition() + Vec3(-2.0 * cos(rotation), 2.5, -2.0 * sin(rotation));
	cam->setViewMatrixAsLookAt(
		transformNode->getPosition() + Vec3(-15.0 * cos(rotation), 2.5, -15.0 * sin(rotation)),
		transformNode->getPosition() + Vec3(0, 1.5, 0),
		osg::Vec3(0, 1, 0));
}

void ControlledCycle::setCyclePosition(float x, float y, float z)
{
	transformNode->setPosition(Vec3(x,y,z));
}

void ControlledCycle::setCyclePosition(Vec3 v)
{
	transformNode->setPosition(v);
}
