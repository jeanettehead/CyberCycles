#ifndef O_H
#define O_H

#include <osg/PositionAttitudeTransform>

using namespace osg;

class Obstacle
{
	public:
		ref_ptr<PositionAttitudeTransform> obsNode;
		float bonusAmount;
		void onDestroy();
		float size;
};

#endif
