#include "mainmenu.h"

MainMenu::MainMenu()
{

}

ref_ptr<Node> MainMenu::getMenuNode(){
	// Declare a box class (derived from shape class) instance
	// This constructor takes an osg::Vec3 to define the center
	 //and a float to define the height, width and depth.
	 //(an overloaded constructor allows you to specify unique
	// height, width and height values.)
	ref_ptr<Box> unitCube = new Box( osg::Vec3(0,0,0), 1.0f);

	// Declare an instance of the shape drawable class and initialize
	// it with the unitCube shape we created above.
	// This class is derived from 'drawable' so instances of this
	// class can be added to Geode instances.
	ref_ptr<ShapeDrawable> unitCubeDrawable = new ShapeDrawable(unitCube);

	// Declare a instance of the geode class:
	ref_ptr<Geode> basicShapesGeode = new Geode();

	// Add the unit cube drawable to the geode:
	basicShapesGeode->addDrawable(unitCubeDrawable);

	// Add the goede to the scene:
	return basicShapesGeode;

}
