#include "plusObstacle.h"
#include <osg/ShapeDrawable>
#include <osg/Geode>

PlusObstacle::PlusObstacle(ref_ptr<StateSet> s, float x, float y, float z)
{
	size = 0.5f;
	obsNode = new PositionAttitudeTransform();
	
	ref_ptr<Geode> obsGeode = new Geode();
	ref_ptr<Box> myBox = new Box(Vec3f(0,0,0), size);
	ref_ptr<ShapeDrawable> boxDrawable (new ShapeDrawable(myBox.get()));
	obsGeode->addDrawable(boxDrawable.get());
	obsNode->setPosition(Vec3d(x, y, z));
	obsNode->setStateSet(s);
	obsNode->addChild(obsGeode);
}
