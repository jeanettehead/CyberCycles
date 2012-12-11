#ifndef PO_H
#define PO_H

#include "obstacle.h"

using namespace osg;

class PlusObstacle : public Obstacle
{
	public:
		PlusObstacle(ref_ptr<StateSet> s, float x, float y, float z);
};

#endif
