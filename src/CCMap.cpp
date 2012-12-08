#include "CCMap.h"
#include <osg/Light>
#include <osg/PositionAttitudeTransform>
#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;

CCMap::CCMap()
{
	genericRoadWidth = 5.0f;
	loadTextures();
	
	//stuff for textures
	texcoords = new Vec2Array(4);
		    	(*texcoords)[0].set(0.0f,1.0f);
			(*texcoords)[1].set(0.0f,0.0f);
	        	(*texcoords)[2].set(1.0f,0.0f);
	 	        (*texcoords)[3].set(1.0f,1.0f);
	normals = new Vec3Array(1);
			(*normals)[0].set(0.0f,1.0f,0.0f);
	colors = new Vec4Array(1);
		    	(*colors)[0].set(1.0f,1.0f,1.0f,1.0f);
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
	roofSet = new StateSet();
	
	//textures
	ref_ptr<Texture2D> roadTexture = new Texture2D();
	ref_ptr<Texture2D> wallTexture = new Texture2D();
	ref_ptr<Texture2D> road90Texture = new Texture2D();
	ref_ptr<Texture2D> startTexture = new Texture2D();
	ref_ptr<Texture2D> finishTexture = new Texture2D();
	ref_ptr<Texture2D> checkpointTexture = new Texture2D();
	ref_ptr<Texture2D> roofTexture = new Texture2D();

	//protect from being optimized away as static state
	roadTexture->setDataVariance(Object::DYNAMIC); 
	wallTexture->setDataVariance(Object::DYNAMIC);
	road90Texture->setDataVariance(Object::DYNAMIC);
	startTexture->setDataVariance(Object::DYNAMIC);
	finishTexture->setDataVariance(Object::DYNAMIC);
	checkpointTexture->setDataVariance(Object::DYNAMIC);
	roofTexture->setDataVariance(Object::DYNAMIC);
	
	// load an image by reading a file: 
	ref_ptr<Image> rtImage = osgDB::readImageFile("../assets/images/tunnel/road.png");
	if (!rtImage)
	{
		std::cout << " couldn't find road texture, quiting." << std::endl;
	}
	ref_ptr<Image> wtImage = osgDB::readImageFile("../assets/images/tunnel/wall.png");
	if (!wtImage)
	{
		std::cout << " couldn't find wall texture, quiting." << std::endl;
	}
	ref_ptr<Image> r90tImage = osgDB::readImageFile("../assets/images/tunnel/road90.png");
	if (!r90tImage)
	{
		std::cout << " couldn't find 90 texture, quiting." << std::endl;
	}
	ref_ptr<Image> stImage = osgDB::readImageFile("../assets/images/tunnel/start.png");
	if (!stImage)
	{
		std::cout << " couldn't find start texture, quiting." << std::endl;
	}
	ref_ptr<Image> ftImage = osgDB::readImageFile("../assets/images/tunnel/finish.png");
	if (!ftImage)
	{
		std::cout << " couldn't find finish texture, quiting." << std::endl;
	}
	ref_ptr<Image> ctImage = osgDB::readImageFile("../assets/images/tunnel/checkpoint.png");
	if (!ctImage)
	{
		std::cout << " couldn't find checpoint texture, quiting." << std::endl;
	}
	ref_ptr<Image> ttImage = osgDB::readImageFile("../assets/images/tunnel/roof.png");
	if (!ttImage)
	{
		std::cout << " couldn't find checpoint texture, quiting." << std::endl;
	}
	
	roadTexture->setImage(rtImage);
	wallTexture->setImage(wtImage);
	road90Texture->setImage(r90tImage);
	startTexture->setImage(stImage);
	finishTexture->setImage(ftImage);
	checkpointTexture->setImage(ctImage);
	roofTexture->setImage(ttImage);
	
	straightRoadSet->setTextureAttributeAndModes(0,roadTexture,StateAttribute::ON);
	road90Set->setTextureAttributeAndModes(0,road90Texture,StateAttribute::ON);
	startSet->setTextureAttributeAndModes(0,startTexture,StateAttribute::ON);
	finishSet->setTextureAttributeAndModes(0,finishTexture,StateAttribute::ON);
	checkpointSet->setTextureAttributeAndModes(0,checkpointTexture,StateAttribute::ON);
	wallSet->setTextureAttributeAndModes(0,wallTexture,StateAttribute::ON);
	roofSet->setTextureAttributeAndModes(0,roofTexture,StateAttribute::ON);
}

void CCMap::buildBuiltInWorld()
{
	mapNode = new Group();
	
	float x;
	float z;
	for(x = -50; x < 50; x = x + genericRoadWidth)
	{
		for(z = 0; z < 5; z = z + genericRoadWidth)
		{
			buildStrightSection(x, 0, z, 0, mapNode);
		}
	}
	buildCheckpointSection(50, 0, 0, 0, mapNode);
	build90Section(55, 0, 0, 0, mapNode);
}

/* Creats a road piece at the given loacation.
 * The loaction should be the upper left corrner, but needs to be checked.
 */
/*void CCMap::buildRoadSection(float x, float y, float z, ref_ptr<Geode> road, ref_ptr<Geode> wall)
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
}*/

void CCMap::buildStrightSection(float x, float y, float z, float rotation, ref_ptr<Group> g)
{
	ref_ptr<PositionAttitudeTransform> transformNode = new PositionAttitudeTransform();
	
	ref_ptr<Geometry> roadGeo = new Geometry();
	ref_ptr<Geometry> wallGeoLeft = new Geometry();
	ref_ptr<Geometry> wallGeoRight = new Geometry();
	ref_ptr<Geometry> wallGeoLeftTop = new Geometry();
	ref_ptr<Geometry> wallGeoRightTop = new Geometry();
	ref_ptr<Geometry> roofGeo = new Geometry();
	
	ref_ptr<Geode> road_node = new Geode();
	ref_ptr<Geode> wall_node = new Geode();
	ref_ptr<Geode> roof_node = new Geode();
	
	float modifier = genericRoadWidth/2.0f;
	
	//verticies for the road piece
	ref_ptr<Vec3Array> roadVert = new Vec3Array;
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 + modifier) );
	
	roadGeo->setVertexArray(roadVert);
	roadGeo->setTexCoordArray(0,texcoords);
        roadGeo->setNormalArray(normals);
    	roadGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roadGeo->setColorArray(colors);
	roadGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roadGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the roof
	float height = 2.0f * genericRoadWidth * cos(M_PI/6.0f);
	ref_ptr<Vec3Array> roofVert = new Vec3Array();
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	
	roofGeo->setVertexArray(roofVert);
	roofGeo->setTexCoordArray(0,texcoords);
        roofGeo->setNormalArray(normals);
    	roofGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roofGeo->setColorArray(colors);
	roofGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roofGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom left
	float half = genericRoadWidth * cos(M_PI/6.0f);
	float out = genericRoadWidth * sin(M_PI/6.0f);
	ref_ptr<Vec3Array> wall1Vert = new Vec3Array();
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	
	wallGeoLeft->setVertexArray(wall1Vert);
	wallGeoLeft->setTexCoordArray(0,texcoords);
        wallGeoLeft->setNormalArray(normals);
    	wallGeoLeft->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeft->setColorArray(colors);
	wallGeoLeft->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeft->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom right
	ref_ptr<Vec3Array> wall2Vert = new Vec3Array();
	wall2Vert->push_back( Vec3( 0 - modifier , 0, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	wall2Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 + modifier + out) );
	wall2Vert->push_back( Vec3( 0 + modifier, 0, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 - modifier , 0, 0 + modifier) );
	
	wallGeoRight->setVertexArray(wall2Vert);
	wallGeoRight->setTexCoordArray(0,texcoords);
        wallGeoRight->setNormalArray(normals);
    	wallGeoRight->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRight->setColorArray(colors);
	wallGeoRight->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRight->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top left
	ref_ptr<Vec3Array> wall3Vert = new Vec3Array();
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier , height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	
	wallGeoLeftTop->setVertexArray(wall3Vert);
	wallGeoLeftTop->setTexCoordArray(0,texcoords);
        wallGeoLeftTop->setNormalArray(normals);
    	wallGeoLeftTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeftTop->setColorArray(colors);
	wallGeoLeftTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeftTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top right
	ref_ptr<Vec3Array> wall4Vert = new Vec3Array();
	wall4Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	wall4Vert->push_back( Vec3( 0 - modifier , height, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, height, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 + modifier + out) );
	wall4Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	
	wallGeoRightTop->setVertexArray(wall4Vert);
	wallGeoRightTop->setTexCoordArray(0,texcoords);
        wallGeoRightTop->setNormalArray(normals);
    	wallGeoRightTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRightTop->setColorArray(colors);
	wallGeoRightTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRightTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//set textures
	road_node->setStateSet(straightRoadSet);
	roof_node->setStateSet(roofSet);
	wall_node->setStateSet(wallSet);
	
	//add geometry to respective nodes
	road_node->addDrawable(roadGeo);
	roof_node->addDrawable(roofGeo);
	wall_node->addDrawable(wallGeoLeft);
	wall_node->addDrawable(wallGeoRight);
	wall_node->addDrawable(wallGeoLeftTop);
	wall_node->addDrawable(wallGeoRightTop);
	
	//add the nodes to the transformNode
	transformNode->addChild(road_node);
	transformNode->addChild(roof_node);
	transformNode->addChild(wall_node);
	
	//move the transform node
	transformNode->setPosition(Vec3(x, y, z));
	transformNode->setAttitude(Quat(0.0, Vec3d(1.0,0.0,0.0), rotation,Vec3d(0.0,1.0,0.0), 0.0, Vec3d(0.0,0.0,1.0)));
	
	//add the transform node to g
	g->addChild(transformNode);
}

void CCMap::build90Section(float x, float y, float z, float rotation, ref_ptr<Group> g)
{
	ref_ptr<PositionAttitudeTransform> transformNode = new PositionAttitudeTransform();
	
	ref_ptr<Geometry> roadGeo = new Geometry();
	ref_ptr<Geometry> wallGeoLeft = new Geometry();
	ref_ptr<Geometry> wallGeoRight = new Geometry(); //in this case right means front
	ref_ptr<Geometry> wallGeoLeftTop = new Geometry();
	ref_ptr<Geometry> wallGeoRightTop = new Geometry();
	ref_ptr<Geometry> roofGeo = new Geometry();
	ref_ptr<Geometry> wallCornGeo = new Geometry();
	ref_ptr<Geometry> wallCornTopGeo = new Geometry();
	
	ref_ptr<Geode> road_node = new Geode();
	ref_ptr<Geode> wall_node = new Geode();
	ref_ptr<Geode> roof_node = new Geode();
	
	float modifier = genericRoadWidth/2.0f;
	
	//verticies for the road piece
	ref_ptr<Vec3Array> roadVert = new Vec3Array;
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 - modifier) );
	
	roadGeo->setVertexArray(roadVert);
	roadGeo->setTexCoordArray(0,texcoords);
        roadGeo->setNormalArray(normals);
    	roadGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roadGeo->setColorArray(colors);
	roadGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roadGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the roof
	float height = 2.0f * genericRoadWidth * cos(M_PI/6.0f);
	ref_ptr<Vec3Array> roofVert = new Vec3Array();
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	
	roofGeo->setVertexArray(roofVert);
	roofGeo->setTexCoordArray(0,texcoords);
        roofGeo->setNormalArray(normals);
    	roofGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roofGeo->setColorArray(colors);
	roofGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roofGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom left
	float half = genericRoadWidth * cos(M_PI/6.0f);
	float out = genericRoadWidth * sin(M_PI/6.0f);
	ref_ptr<Vec3Array> wall1Vert = new Vec3Array();
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	
	wallGeoLeft->setVertexArray(wall1Vert);
	wallGeoLeft->setTexCoordArray(0,texcoords);
        wallGeoLeft->setNormalArray(normals);
    	wallGeoLeft->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeft->setColorArray(colors);
	wallGeoLeft->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeft->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom right (front)
	ref_ptr<Vec3Array> wall2Vert = new Vec3Array();
	wall2Vert->push_back( Vec3( 0 + modifier , 0, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 + modifier + out, 0 + half, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 + modifier + out, 0 + half, 0 - modifier) );
	wall2Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	wall2Vert->push_back( Vec3( 0 + modifier , 0, 0 + modifier) );
	
	wallGeoRight->setVertexArray(wall2Vert);
	wallGeoRight->setTexCoordArray(0,texcoords);
        wallGeoRight->setNormalArray(normals);
    	wallGeoRight->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRight->setColorArray(colors);
	wallGeoRight->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRight->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top left
	ref_ptr<Vec3Array> wall3Vert = new Vec3Array();
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier , height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	
	wallGeoLeftTop->setVertexArray(wall3Vert);
	wallGeoLeftTop->setTexCoordArray(0,texcoords);
        wallGeoLeftTop->setNormalArray(normals);
    	wallGeoLeftTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeftTop->setColorArray(colors);
	wallGeoLeftTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeftTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top right (front)
	ref_ptr<Vec3Array> wall4Vert = new Vec3Array();
	wall4Vert->push_back( Vec3( 0 + modifier + out, 0 + half, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, height, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier + out, half, 0 - modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier + out, half, 0 + modifier) );
	
	wallGeoRightTop->setVertexArray(wall4Vert);
	wallGeoRightTop->setTexCoordArray(0,texcoords);
        wallGeoRightTop->setNormalArray(normals);
    	wallGeoRightTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRightTop->setColorArray(colors);
	wallGeoRightTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRightTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall corrner bottom
	ref_ptr<Vec3Array> wall5Vert = new Vec3Array();
	wall5Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	wall5Vert->push_back( Vec3( 0 + modifier, half, 0 - modifier - out) );
	wall5Vert->push_back( Vec3( 0 + modifier + out, half, 0 - modifier) );
	wall5Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	
	wallCornGeo->setVertexArray(wall5Vert);
	wallCornGeo->setTexCoordArray(0,texcoords);
        wallCornGeo->setNormalArray(normals);
    	wallCornGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	wallCornGeo->setColorArray(colors);
	wallCornGeo->setColorBinding(Geometry::BIND_OVERALL);	
	wallCornGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall corrner top
	ref_ptr<Vec3Array> wall6Vert = new Vec3Array();
	wall6Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );	
	wall6Vert->push_back( Vec3( 0 + modifier + out, half, 0 - modifier) );	
	wall6Vert->push_back( Vec3( 0 + modifier, half, 0 - modifier - out) );
	wall6Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );
		
	wallCornTopGeo->setVertexArray(wall6Vert);
	wallCornTopGeo->setTexCoordArray(0,texcoords);
        wallCornTopGeo->setNormalArray(normals);
    	wallCornTopGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	wallCornTopGeo->setColorArray(colors);
	wallCornTopGeo->setColorBinding(Geometry::BIND_OVERALL);	
	wallCornTopGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//set textures
	road_node->setStateSet(road90Set);
	roof_node->setStateSet(roofSet);
	wall_node->setStateSet(wallSet);
	
	//add geometry to respective nodes
	road_node->addDrawable(roadGeo);
	roof_node->addDrawable(roofGeo);
	wall_node->addDrawable(wallGeoLeft);
	wall_node->addDrawable(wallGeoRight);
	wall_node->addDrawable(wallGeoLeftTop);
	wall_node->addDrawable(wallGeoRightTop);
	wall_node->addDrawable(wallCornGeo);
	wall_node->addDrawable(wallCornTopGeo);
	
	//add the nodes to the transformNode
	transformNode->addChild(road_node);
	transformNode->addChild(roof_node);
	transformNode->addChild(wall_node);
	
	//move the transform node
	transformNode->setPosition(Vec3(x, y, z));
	transformNode->setAttitude(Quat(0.0, Vec3d(1.0,0.0,0.0), rotation,Vec3d(0.0,1.0,0.0), 0.0, Vec3d(0.0,0.0,1.0)));
	
	//add the transform node to g
	g->addChild(transformNode);
}

void CCMap::buildCheckpointSection(float x, float y, float z, float rotation, ref_ptr<Group> g)
{
	ref_ptr<PositionAttitudeTransform> transformNode = new PositionAttitudeTransform();
	
	ref_ptr<Geometry> roadGeo = new Geometry();
	ref_ptr<Geometry> wallGeoLeft = new Geometry();
	ref_ptr<Geometry> wallGeoRight = new Geometry();
	ref_ptr<Geometry> wallGeoLeftTop = new Geometry();
	ref_ptr<Geometry> wallGeoRightTop = new Geometry();
	ref_ptr<Geometry> roofGeo = new Geometry();
	
	ref_ptr<Geode> road_node = new Geode();
	ref_ptr<Geode> wall_node = new Geode();
	ref_ptr<Geode> roof_node = new Geode();
	
	float modifier = genericRoadWidth/2.0f;
	
	//verticies for the road piece
	ref_ptr<Vec3Array> roadVert = new Vec3Array;
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 + modifier) );
	roadVert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 - modifier) );
	roadVert->push_back( Vec3( 0 - modifier, 0, 0 + modifier) );
	
	roadGeo->setVertexArray(roadVert);
	roadGeo->setTexCoordArray(0,texcoords);
        roadGeo->setNormalArray(normals);
    	roadGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roadGeo->setColorArray(colors);
	roadGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roadGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the roof
	float height = 2.0f * genericRoadWidth * cos(M_PI/6.0f);
	ref_ptr<Vec3Array> roofVert = new Vec3Array();
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 + modifier) );
	roofVert->push_back( Vec3( 0 + modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 - modifier) );
	roofVert->push_back( Vec3( 0 - modifier, 0 + height, 0 + modifier) );
	
	roofGeo->setVertexArray(roofVert);
	roofGeo->setTexCoordArray(0,texcoords);
        roofGeo->setNormalArray(normals);
    	roofGeo->setNormalBinding(Geometry::BIND_OVERALL);
    	roofGeo->setColorArray(colors);
	roofGeo->setColorBinding(Geometry::BIND_OVERALL);	
	roofGeo->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom left
	float half = genericRoadWidth * cos(M_PI/6.0f);
	float out = genericRoadWidth * sin(M_PI/6.0f);
	ref_ptr<Vec3Array> wall1Vert = new Vec3Array();
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall1Vert->push_back( Vec3( 0 + modifier, 0, 0 - modifier) );
	wall1Vert->push_back( Vec3( 0 - modifier , 0, 0 - modifier) );
	
	wallGeoLeft->setVertexArray(wall1Vert);
	wallGeoLeft->setTexCoordArray(0,texcoords);
        wallGeoLeft->setNormalArray(normals);
    	wallGeoLeft->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeft->setColorArray(colors);
	wallGeoLeft->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeft->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall bottom right
	ref_ptr<Vec3Array> wall2Vert = new Vec3Array();
	wall2Vert->push_back( Vec3( 0 - modifier , 0, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	wall2Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 + modifier + out) );
	wall2Vert->push_back( Vec3( 0 + modifier, 0, 0 + modifier) );
	wall2Vert->push_back( Vec3( 0 - modifier , 0, 0 + modifier) );
	
	wallGeoRight->setVertexArray(wall2Vert);
	wallGeoRight->setTexCoordArray(0,texcoords);
        wallGeoRight->setNormalArray(normals);
    	wallGeoRight->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRight->setColorArray(colors);
	wallGeoRight->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRight->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top left
	ref_ptr<Vec3Array> wall3Vert = new Vec3Array();
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier , height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, height, 0 - modifier) );
	wall3Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 - modifier - out) );
	wall3Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 - modifier - out) );
	
	wallGeoLeftTop->setVertexArray(wall3Vert);
	wallGeoLeftTop->setTexCoordArray(0,texcoords);
        wallGeoLeftTop->setNormalArray(normals);
    	wallGeoLeftTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoLeftTop->setColorArray(colors);
	wallGeoLeftTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoLeftTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//verticies for the wall top right
	ref_ptr<Vec3Array> wall4Vert = new Vec3Array();
	wall4Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	wall4Vert->push_back( Vec3( 0 - modifier , height, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, height, 0 + modifier) );
	wall4Vert->push_back( Vec3( 0 + modifier, 0 + half, 0 + modifier + out) );
	wall4Vert->push_back( Vec3( 0 - modifier, 0 + half, 0 + modifier + out) );
	
	wallGeoRightTop->setVertexArray(wall4Vert);
	wallGeoRightTop->setTexCoordArray(0,texcoords);
        wallGeoRightTop->setNormalArray(normals);
    	wallGeoRightTop->setNormalBinding(Geometry::BIND_OVERALL);
    	wallGeoRightTop->setColorArray(colors);
	wallGeoRightTop->setColorBinding(Geometry::BIND_OVERALL);	
	wallGeoRightTop->addPrimitiveSet(new DrawArrays(GL_QUADS,0,4)); //I am not sure what this actuall does
	
	//set textures
	road_node->setStateSet(checkpointSet);
	roof_node->setStateSet(checkpointSet);
	wall_node->setStateSet(checkpointSet);
	
	//add geometry to respective nodes
	road_node->addDrawable(roadGeo);
	roof_node->addDrawable(roofGeo);
	wall_node->addDrawable(wallGeoLeft);
	wall_node->addDrawable(wallGeoRight);
	wall_node->addDrawable(wallGeoLeftTop);
	wall_node->addDrawable(wallGeoRightTop);
	
	//add the nodes to the transformNode
	transformNode->addChild(road_node);
	transformNode->addChild(roof_node);
	transformNode->addChild(wall_node);
	
	//move the transform node
	transformNode->setPosition(Vec3(x, y, z));
	transformNode->setAttitude(Quat(0.0, Vec3d(1.0,0.0,0.0), rotation,Vec3d(0.0,1.0,0.0), 0.0, Vec3d(0.0,0.0,1.0)));
	
	//add the transform node to g
	g->addChild(transformNode);
}

ref_ptr<Group> CCMap::getMapNode()
{
	return mapNode;
}
