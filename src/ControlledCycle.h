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
		double rotation;
		
	private:
		ref_ptr<PositionAttitudeTransform> transformNode;
		ref_ptr<Group> cycle;
		ref_ptr<Node> model;
};

#endif
