#include "CCMap.h"
#include <osg/Light>
#include <iostream>

using namespace std;

CCMap::CCMap()
{
	genericRoadWidth = 5.0f;
}

void CCMap::buildBuiltInWorld()
{
	mapNode = new Group();
	
	//node that the road pices are added to
	ref_ptr<Geode> road_node = new Geode();
	
	float x;
	for(x = 0; x < 5; x = x + genericRoadWidth)
	{
		float z;
		for(z = -50; z < 50; z = z + genericRoadWidth)
		{
			road_node->addDrawable(buildRoadPiece((float)x, 0, (float)z));
		}
	}
	
	//texture
	Texture2D* roadTexture = new Texture2D;

	// protect from being optimized away as static state:
	roadTexture->setDataVariance(Object::DYNAMIC); 

	// load an image by reading a file: 
	Image* klnFace = osgDB::readImageFile("../assets/road.png");
	if (!klnFace)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
	}

   	// Assign the texture to the image we read from file: 
  	 roadTexture->setImage(klnFace);
	// Create a new StateSet with default settings: 
	StateSet* stateOne = new StateSet();

	// Assign texture unit 0 of our new StateSet to the texture 
	// we just created and enable the texture.
	stateOne->setTextureAttributeAndModes(0,roadTexture,StateAttribute::ON);
	
	road_node->setStateSet(stateOne);
	
	mapNode->addChild(road_node);
}

/* Creats a road piece at the given loacation.
 * The loaction should be the upper left corrner, but needs to be checked.
 */
ref_ptr<Geometry> CCMap::buildRoadPiece(float x, float y, float z)
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
	
	return myPlane;
}

ref_ptr<Group> CCMap::getMapNode()
{
	return mapNode;
}
