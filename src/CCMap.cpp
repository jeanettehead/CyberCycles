#include "CCMap.h"
#include <osg/Light>
#include <iostream>

using namespace std;

CCMap::CCMap()
{
	genericRoadWidth = 5.0f;
	loadTextures();
}

void CCMap::loadTextures()
{
	//intilize state sets
	straightRoadSet = new StateSet();
	road90Set = new StateSet();
	startSet = new StateSet();
	finishSet = new StateSet();
	checkpointSet = new StateSet();
	wallSet = new StateSet();
	
	//textures
	ref_ptr<Texture2D> roadTexture = new Texture2D();
	ref_ptr<Texture2D> wallTexture = new Texture2D();
	ref_ptr<Texture2D> road90Texture = new Texture2D();
	ref_ptr<Texture2D> startTexture = new Texture2D();
	ref_ptr<Texture2D> finishTexture = new Texture2D();
	ref_ptr<Texture2D> checkpointTexture = new Texture2D();

	//protect from being optimized away as static state
	roadTexture->setDataVariance(Object::DYNAMIC); 
	wallTexture->setDataVariance(Object::DYNAMIC);
	road90Texture->setDataVariance(Object::DYNAMIC);
	startTexture->setDataVariance(Object::DYNAMIC);
	finishTexture->setDataVariance(Object::DYNAMIC);
	checkpointTexture->setDataVariance(Object::DYNAMIC);
	
	// load an image by reading a file: 
	Image* rtImage = osgDB::readImageFile("../assets/images/tunnel/road.png");
	if (!rtImage)
	{
		std::cout << " couldn't find road texture, quiting." << std::endl;
	}
	Image* wtImage = osgDB::readImageFile("../assets/images/tunnel/wall.png");
	if (!wtImage)
	{
		std::cout << " couldn't find wall texture, quiting." << std::endl;
	}
	Image* r90tImage = osgDB::readImageFile("../assets/images/tunnel/road90.png");
	if (!r90tImage)
	{
		std::cout << " couldn't find 90 texture, quiting." << std::endl;
	}
	Image* stImage = osgDB::readImageFile("../assets/images/tunnel/start.png");
	if (!stImage)
	{
		std::cout << " couldn't find start texture, quiting." << std::endl;
	}
	Image* ftImage = osgDB::readImageFile("../assets/images/tunnel/finish.png");
	if (!ftImage)
	{
		std::cout << " couldn't find finish texture, quiting." << std::endl;
	}
	Image* ctImage = osgDB::readImageFile("../assets/images/tunnel/checkpoint.png");
	if (!ctImage)
	{
		std::cout << " couldn't find checpoint texture, quiting." << std::endl;
	}
		
	straightRoadSet->setTextureAttributeAndModes(0,roadTexture,StateAttribute::ON);
	road90Set->setTextureAttributeAndModes(0,road90Texture,StateAttribute::ON);
	startSet->setTextureAttributeAndModes(0,startTexture,StateAttribute::ON);
	finishSet->setTextureAttributeAndModes(0,finishTexture,StateAttribute::ON);
	checkpointSet->setTextureAttributeAndModes(0,checkpointTexture,StateAttribute::ON);
	wallSet->setTextureAttributeAndModes(0,wallTexture,StateAttribute::ON);
}

void CCMap::buildBuiltInWorld()
{
	mapNode = new Group();
	
	//node that the road pices are added to
	ref_ptr<Geode> road_node = new Geode();
	ref_ptr<Geode> wall_node = new Geode();
	
	float x;
	for(x = 0; x < 5; x = x + genericRoadWidth)
	{
		float z;
		for(z = -50; z < 50; z = z + genericRoadWidth)
		{
			buildRoadSection((float)x, 0, (float)z, road_node, wall_node);
		}
	}
	
	//texture
	Texture2D* roadTexture = new Texture2D;
	Texture2D* wallTexture = new Texture2D;

	// protect from being optimized away as static state:
	roadTexture->setDataVariance(Object::DYNAMIC); 
	wallTexture->setDataVariance(Object::DYNAMIC);

	// load an image by reading a file: 
	Image* rtImage = osgDB::readImageFile("../assets/road.png");
	if (!rtImage)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
	}
	Image* wtImage = osgDB::readImageFile("../assets/wall.png");
	if (!wtImage)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
	}

   	// Assign the texture to the image we read from file: 
	roadTexture->setImage(rtImage);
	wallTexture->setImage(wtImage);
	// Create a new StateSet with default settings: 
	StateSet* roadState = new StateSet();
	StateSet* wallState = new StateSet();

	// Assign texture unit 0 of our new StateSet to the texture 
	// we just created and enable the texture.
	roadState->setTextureAttributeAndModes(0,roadTexture,StateAttribute::ON);
	wallState->setTextureAttributeAndModes(0,wallTexture,StateAttribute::ON);
	
	road_node->setStateSet(roadState);
	wall_node->setStateSet(wallState);
	
	mapNode->addChild(road_node);
	mapNode->addChild(wall_node);
}

/* Creats a road piece at the given loacation.
 * The loaction should be the upper left corrner, but needs to be checked.
 */
void CCMap::buildRoadSection(float x, float y, float z, ref_ptr<Geode> road, ref_ptr<Geode> wall)
{
	//the geometry for the road piece
	ref_ptr<Geometry> myPlane (new Geometry());
	//verticies for the road piece
	Vec3Array* roadVert = new Vec3Array;
	roadVert->push_back( Vec3( x, y, z) ); // front left
	roadVert->push_back( Vec3( x, y, z + genericRoadWidth) ); // front right
	roadVert->push_back( Vec3( x + genericRoadWidth, y, z + genericRoadWidth) ); // back right 
	roadVert->push_back( Vec3( x + genericRoadWidth, y, z) ); // front left
	roadVert->push_back( Vec3( x, y, z) ); // front left
	
	//some more stuff to take care of
	Vec2Array* texcoords = new Vec2Array(4);
		    	(*texcoords)[0].set(0.0f,1.0f);
			(*texcoords)[1].set(0.0f,0.0f);
	        	(*texcoords)[2].set(1.0f,0.0f);
	 	        (*texcoords)[3].set(1.0f,1.0f);
	Vec3Array* normals = new Vec3Array(1);
			(*normals)[0].set(0.0f,1.0f,0.0f);
	Vec4Array* colors = new Vec4Array(1);
		    	(*colors)[0].set(1.0f,1.0f,1.0f,1.0f);
		    	
	myPlane->setVertexArray(roadVert);
	myPlane->setTexCoordArray(0,texcoords);
        myPlane->setNormalArray(normals);
    	myPlane->setNormalBinding(Geometry::BIND_OVERALL);
    	myPlane->setColorArray(colors);
	myPlane->setColorBinding(Geometry::BIND_OVERALL);	
	myPlane->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	road->addDrawable(myPlane);	
}

void CCMap::buildStrightSection(float x, float y, float z, ref_ptr<Geode> g)
{
}

ref_ptr<Group> CCMap::getMapNode()
{
	return mapNode;
}
