#include "CCMap.h"
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
	osg::Texture2D* KLN89FaceTexture = new osg::Texture2D;

	// protect from being optimized away as static state:
	KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

	// load an image by reading a file: 
	osg::Image* klnFace = osgDB::readImageFile("../assets/TronBackground.jpg");
	if (!klnFace)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
	}

   	// Assign the texture to the image we read from file: 
  	 KLN89FaceTexture->setImage(klnFace);
	// Create a new StateSet with default settings: 
	osg::StateSet* stateOne = new osg::StateSet();

	// Assign texture unit 0 of our new StateSet to the texture 
	// we just created and enable the texture.
	stateOne->setTextureAttributeAndModes
	(0,KLN89FaceTexture,osg::StateAttribute::ON);
	// Associate this state set with the Geode that contains
	// the pyramid: 
	road_node->setStateSet(stateOne);
	
	mapNode->addChild(road_node);
}

/* Creats a road piece at the given loacation.
 * The loaction should be the upper left corrner, but needs to be checked.
 */
ref_ptr<Geometry> CCMap::buildRoadPiece(float x, float y, float z)
{
	//the geometry for the road piece
	osg::ref_ptr<osg::Geometry> myPlane (new osg::Geometry());
	//verticies for the road piece
	Vec3Array* roadVert = new Vec3Array;
	roadVert->push_back( Vec3( x, y, z) ); // front left
	roadVert->push_back( Vec3( x, y, z + genericRoadWidth) ); // front right
	roadVert->push_back( Vec3( x + genericRoadWidth, y, z + genericRoadWidth) ); // back right 
	roadVert->push_back( Vec3( x + genericRoadWidth, y, z) ); // front left
	roadVert->push_back( Vec3( x, y, z) ); // front left
	
	//some more stuff to take care of
	osg::Vec2Array* texcoords = new osg::Vec2Array(4);
		    	(*texcoords)[0].set(0.0f,1.0f);
			(*texcoords)[1].set(0.0f,0.0f);
	        	(*texcoords)[2].set(1.0f,0.0f);
	 	        (*texcoords)[3].set(1.0f,1.0f);
	osg::Vec3Array* normals = new osg::Vec3Array(1);
			(*normals)[0].set(0.0f,1.0f,0.0f);
	osg::Vec4Array* colors = new osg::Vec4Array(1);
		    	(*colors)[0].set(1.0f,1.0f,1.0f,1.0f);
		    	
	myPlane->setVertexArray(roadVert);
	myPlane->setTexCoordArray(0,texcoords);
        myPlane->setNormalArray(normals);
    	myPlane->setNormalBinding(osg::Geometry::BIND_OVERALL);
    	myPlane->setColorArray(colors);
	myPlane->setColorBinding(osg::Geometry::BIND_OVERALL);	
	myPlane->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	return myPlane;
}

ref_ptr<Group> CCMap::getMapNode()
{
	return mapNode;
}
