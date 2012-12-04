#ifndef CCMAP_H
#define CCMAP_H

#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osgDB/ReadFile> 

using namespace osg;

class CCMap
{
	public:
		CCMap();
		ref_ptr<Group> getMapNode();
		void buildBuiltInWorld();
		float genericRoadWidth;
		
	private:
		ref_ptr<Group> mapNode;
		ref_ptr<Geometry> buildRoadPiece(float x, float y, float z);
		
};

#endif
