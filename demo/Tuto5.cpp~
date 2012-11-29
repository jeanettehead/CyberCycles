#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osg/StateSet>
#include <osgDB/ReadFile> 
#include <osgGA/GUIEventHandler>
#include <iostream>
#include <math.h>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgGA/NodeTrackerManipulator>
#include <osgParticle/PrecipitationEffect>
#include <osg/Camera>
#include <osgGA/TrackballManipulator>
#include <osg/Quat>
#include <osg/Light>

#define _USE_MATH_DEFINES
using namespace std;
//#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/StateSetManipulator>

osg::PositionAttitudeTransform* sphereXForm = NULL;
osg::ref_ptr<osg::Node> cycle = NULL;
osg::ref_ptr<osg::Camera> myCam = new osg::Camera;
osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
double rot = 0.0;

bool upkey = false;
bool downkey = false;
bool leftkey = false;
bool rightkey = false;

class myKeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};

bool myKeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
					
	     		if(ea.getKey() == 'w')
			{
				//upkey = true;
				std::cout << " w key pressed" << std::endl;
				sphereXForm->setPosition(osg::Vec3(1.0 * cos(rot),0, 1.0 * sin(rot)) + sphereXForm->getPosition());
				myCam->setViewMatrixAsLookAt(
					sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
					sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
					osg::Vec3(0, 1, 0));   // usual up vector				
				//return false;
				//break;
			}
			if(ea.getKey() == 's')
			{
				//downkey = true;
				std::cout << " s key pressed" << std::endl;
				sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0 * cos(rot),0, 1.0 * sin(rot)));
				myCam->setViewMatrixAsLookAt(
					sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
					sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
					osg::Vec3(0, 1, 0));   // usual up vector
				//return false;
				//break;
			}
			if(ea.getKey() == 'd')
			{
				//rightkey = true;
				std::cout << " d key pressed" << std::endl;
				rot = rot + M_PI/36.0;				
				sphereXForm->setAttitude(osg::Quat(M_PI, osg::Vec3d(1.0,0.0,0.0), rot,osg::Vec3d(0.0,-1.0,0.0), 0.0, osg::Vec3d(0.0,0.0,0.0)));
				//sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0,0,0));
				myCam->setViewMatrixAsLookAt(
					sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
					sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
					osg::Vec3(0, 1, 0));   // usual up vector
				//return false;
			}
				//break;
			if(ea.getKey() == 'a')
			{
				//leftkey = true;
				std::cout << " d key pressed" << std::endl;
				rot = rot - M_PI/36.0;				
				sphereXForm->setAttitude(osg::Quat(M_PI, osg::Vec3d(1.0,0.0,0.0), rot,osg::Vec3d(0.0,-1.0,0.0), 0.0, osg::Vec3d(0.0,0.0,0.0)));
				//sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0,0,0));
				myCam->setViewMatrixAsLookAt(
					sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
					sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
					osg::Vec3(0, 1, 0));   // usual up vector
				//return false;
			}
			return false;
  		}
	/*case(osgGA::GUIEventAdapter::KEYUP):
	{
		if(ea.getKey() == 'w')
		{
			upkey = false;
		}		
		if(ea.getKey() == 's')
		{
			std::cout << " s key released" << std::endl;
			downkey == false;
		}		
		if(ea.getKey() == 'd')
		{
			rightkey == false;
		}
		if(ea.getKey() == 'a')
		{
			leftkey == false;
		}
	}*/
	default:
		return false;
	}
}

int main()
{	
	//Creating the viewer	
    	osgViewer::Viewer viewer ;
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	

	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);
	//viewer.setSceneData( root.get() );

	//The geode containing our shpae
   	osg::ref_ptr<osg::Geode> myshapegeode (new osg::Geode);
	
	//Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
	osg::ref_ptr<osg::Box> myCapsule (new osg::Box(osg::Vec3f(0,0,0), 1.0f));

	osg::Vec2Array* texcoords = new osg::Vec2Array(4);
		    	(*texcoords)[0].set(0.0f,1.0f);
			(*texcoords)[1].set(0.0f,0.0f);
	        	(*texcoords)[2].set(1.0f,0.0f);
	 	        (*texcoords)[3].set(1.0f,1.0f);
	osg::Vec3Array* normals = new osg::Vec3Array(1);
			(*normals)[0].set(0.0f,1.0f,0.0f);
	osg::Vec4Array* colors = new osg::Vec4Array(1);
		    	(*colors)[0].set(1.0f,1.0f,1.0f,1.0f);
	int x = -100;
	bool tog = true;
	for(x = -100; x <= 100; x = x + 5)
	{ 
		int y = -100;
		for(y = -100; y <= 100; y = y + 5)
		{
			osg::ref_ptr<osg::Geometry> myPlane (new osg::Geometry());
	
			//plane verticies
			osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
			pyramidVertices->push_back( osg::Vec3( x, 0, y) ); // front left
			pyramidVertices->push_back( osg::Vec3( x, 0, y + 5) ); // front right
			pyramidVertices->push_back( osg::Vec3( x + 5, 0, y + 5) ); // back right 
			pyramidVertices->push_back( osg::Vec3( x + 5, 0, y) ); // front left
			pyramidVertices->push_back( osg::Vec3( x, 0, y) ); // front left
			//pyramidVertices->push_back( osg::Vec3( 1, 0, 0) ); // back left 
			//pyramidVertices->push_back( osg::Vec3( 1, 1, 0) ); // peak
			//pyramidVertices->push_back( osg::Vec3( 0, 1, 0) ); // peak
			myPlane->setVertexArray(pyramidVertices);
	
	 	 	myPlane->setTexCoordArray(0,texcoords);
			
		        myPlane->setNormalArray(normals);
		    	myPlane->setNormalBinding(osg::Geometry::BIND_OVERALL);
			
		    	myPlane->setColorArray(colors);
    			myPlane->setColorBinding(osg::Geometry::BIND_OVERALL);
	
    			myPlane->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
			myshapegeode->addDrawable(myPlane);

			/*if(tog)
			{
				osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
 				ls->getLight()->setPosition(osg::Vec4(x + 2.5, 10, y + 2.5, 0)); // make 4th coord 1 for point
				//ls->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
				//ls->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
				//ls->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
				ls->getLight()->setDirection(osg::Vec3d(0.0,-1.0,0.0));
				ls->getLight()->setSpotCutoff(0.1745f);
				root->addChild(ls.get());
			}*/
			tog = !tog;
		}
	}

	//texture
	osg::Texture2D* KLN89FaceTexture = new osg::Texture2D;

	// protect from being optimized away as static state:
	KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

	// load an image by reading a file: 
	osg::Image* klnFace = osgDB::readImageFile("TronBackground.jpg");
	if (!klnFace)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
		return -1;
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
	myshapegeode->setStateSet(stateOne);

	//Our shape drawable
	osg::ref_ptr<osg::ShapeDrawable> capsuledrawable (new osg::ShapeDrawable(myCapsule.get()));
	//osg::ref_ptr<osg::ShapeDrawable> planedrawable (new osg::ShapeDrawable(myPlane.get()));
	
	//myshapegeode->addDrawable(capsuledrawable.get());

	root->addChild(myshapegeode.get());
	
	//model loading test
	sphereXForm = new osg::PositionAttitudeTransform();
	sphereXForm->setPosition(osg::Vec3(0,0,0));
	sphereXForm->setAttitude(osg::Quat(M_PI, osg::Vec3(1,0,0)));
	cycle = osgDB::readNodeFile("Light Cycle/HQ_Movie cycle.obj");
	root->addChild(sphereXForm);
	sphereXForm->addChild(cycle);

	myCam->setClearColor(osg::Vec4(0, 0, 255, 1)); // black background
 	// set dimensions of the view volume
	myCam->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
	myCam->setViewMatrixAsLookAt(
		osg::Vec3(-7.5, 7.5, 0), // eye above xy-plane
		sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
		osg::Vec3(0, 1, 0));   // usual up vector
	
 	/*ls->getLight()->setPosition(osg::Vec4(0, 10, 0, 0)); // make 4th coord 1 for point
	ls->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	ls->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
	ls->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	ls->getLight()->setDirection(osg::Vec3d(0.0,-1.0,0.0));
	ls->getLight()->setSpotCutoff(0.1745f);
	root->addChild(ls.get());*/

	//wireframe
	/*osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();
	osg::ref_ptr<osg::PolygonMode> pm;
	pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	ss->setAttributeAndModes(pm.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	cycle->setStateSet(ss);*/

	//viewer.setThreadingModel(osgViewer::Viewer::ThreadingModel::SingleThreaded);
	
	//Stats Event Handler s key
	//viewer.addEventHandler(new osgViewer::StatsHandler);

	//Windows size handler
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	
	// add the state manipulator
    	//viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
	//The viewer.run() method starts the threads and the traversals.
	
	//input
	myKeyboardEventHandler* myFirstEventHandler = new myKeyboardEventHandler();
	viewer.addEventHandler(myFirstEventHandler);

	//camera stuff maybe
	/*osg::ref_ptr<osgGA::NodeTrackerManipulator> ntm = new osgGA::NodeTrackerManipulator;
	ntm->setNode(cycle.get());
	ntm->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER);
	viewer.setCameraManipulator(ntm.get());*/

	//osg::ref_ptr<osgParticle::PrecipitationEffect> precipNode = new osgParticle::PrecipitationEffect();
 	//precipNode->setWind(osg::Vec3(xdir, ydir, zdir));
 	//precipNode->setParticleSpeed(0.4f);
 	//precipNode->snow(0.3f); // alternatively, use snow
 	//root->addChild(precipNode.get());
	
	//viewer.setCameraManipulator(NULL);
	viewer.setCamera(myCam);
	viewer.setSceneData(root);
	//return (viewer.run());
	//viewer.setUpViewer(osgProducer::Viewer::STANDARD_SETTINGS);
	
       	viewer.realize();
	while( !viewer.done() )
	{
     		/*if(upkey)
		{
			//std::cout << " w key pressed" << std::endl;
			sphereXForm->setPosition(osg::Vec3(1.0 * cos(rot),0, 1.0 * sin(rot)) + sphereXForm->getPosition());
			myCam->setViewMatrixAsLookAt(
			sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
			sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
			osg::Vec3(0, 1, 0));   // usual up vector				
		}
		if(downkey)
		{
			//std::cout << " s key pressed" << std::endl;
			sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0 * cos(rot),0, 1.0 * sin(rot)));
			myCam->setViewMatrixAsLookAt(
			sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
			sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
			osg::Vec3(0, 1, 0));   // usual up vector
			
		}
		if(rightkey)
		{
			//std::cout << " d key pressed" << std::endl;
			rot = rot + M_PI/36.0;				
			sphereXForm->setAttitude(osg::Quat(M_PI, osg::Vec3d(1.0,0.0,0.0), rot,osg::Vec3d(0.0,-1.0,0.0), 0.0, osg::Vec3d(0.0,0.0,0.0)));
			//sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0,0,0));
			myCam->setViewMatrixAsLookAt(
				sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
				sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
				osg::Vec3(0, 1, 0));   // usual up vector
		}
		if(leftkey)
		{
			//std::cout << " a key pressed" << std::endl;
			rot = rot - M_PI/36.0;				
			sphereXForm->setAttitude(osg::Quat(M_PI, osg::Vec3d(1.0,0.0,0.0), rot,osg::Vec3d(0.0,-1.0,0.0), 0.0, osg::Vec3d(0.0,0.0,0.0)));
			//sphereXForm->setPosition(sphereXForm->getPosition() - osg::Vec3(1.0,0,0));
			myCam->setViewMatrixAsLookAt(
				sphereXForm->getPosition() + osg::Vec3(-7.5 * cos(rot), 7.5, -7.5 * sin(rot)), // eye above xy-plane
				sphereXForm->getPosition() + osg::Vec3(0, 3, 0),    // gaze at cycle
				osg::Vec3(0, 1, 0));   // usual up vector
		}*/
		viewer.frame();
		viewer.requestRedraw();
	}
}
