#ifndef CONCYC_H
#define CONCYC_H

#include <osg/PositionAttitudeTransform>
#include <osg/Camera>

using namespace osg;

class ControlledCycle
{
	public:
		ControlledCycle();
		ref_ptr<Node> getNode();
		Vec3 getPosition();
		void setCameraPosition(ref_ptr<Camera> cam);
		void setCyclePosition(float x, float y, float z);
		void setCyclePosition(Vec3 v);
		
	private:
		PositionAttitudeTransform* transformNode;
		ref_ptr<Node> cycle;
		double rotation;
};

#endif
