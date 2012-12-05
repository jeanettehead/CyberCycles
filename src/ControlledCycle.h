#ifndef CONCYC_H
#define CONCYC_H

#include <osg/PositionAttitudeTransform>
#include <osg/Camera>
#include <osg/LightSource>
#include <osg/Light>

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
		PositionAttitudeTransform* transformNode;
		ref_ptr<Node> cycle;
		ref_ptr<Light> diffuseLight;
};

#endif
