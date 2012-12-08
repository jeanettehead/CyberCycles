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
		//void buildRoadSection(float x, float y, float z, ref_ptr<Geode> road, ref_ptr<Geode> wall);
		void buildStrightSection(float x, float y, float z, float rotation, ref_ptr<Group> g);
		void build90Section(float x, float y, float z, float rotation, ref_ptr<Group> g);
		void buildCheckpointSection(float x, float y, float z, float rotation, ref_ptr<Group> g);
		void buildStartSection(float x, float y, float z, float rotation, ref_ptr<Group> g);
		void buildFinishSection(float x, float y, float z, float rotation, ref_ptr<Group> g);
		//these are for the textures
		ref_ptr<StateSet> straightRoadSet;
		ref_ptr<StateSet> road90Set;
		ref_ptr<StateSet> startSet;
		ref_ptr<StateSet> finishSet;
		ref_ptr<StateSet> checkpointSet;
		ref_ptr<StateSet> wallSet;
		ref_ptr<StateSet> roofSet;
		void loadTextures();
		ref_ptr<Vec2Array> texcoords;
		ref_ptr<Vec3Array> normals;
		ref_ptr<Vec4Array> colors;
};

#endif
