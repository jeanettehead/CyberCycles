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
		void buildRoadSection(float x, float y, float z, ref_ptr<Geode> road, ref_ptr<Geode> wall);
		void buildStrightSection(float x, float y, float z, ref_ptr<Geode> g);
		//these are for the textures
		ref_ptr<StateSet> straightRoadSet;
		ref_ptr<StateSet> road90Set;
		ref_ptr<StateSet> startSet;
		ref_ptr<StateSet> finishSet;
		ref_ptr<StateSet> checkpointSet;
		ref_ptr<StateSet> wallSet;
		void loadTextures();
				
};

#endif
