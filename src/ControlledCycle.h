#ifndef CONCYC_H
#define CONCYC_H

#include <osg/PositionAttitudeTransform>

using namespace osg;

class ControlledCycle
{
	public:
		ControlledCycle();
		ref_ptr<Node> getNode();
		Vec3 getPosition();
		
	private:
		PositionAttitudeTransform* transformNode;
		ref_ptr<Node> cycle;
};

#endif
