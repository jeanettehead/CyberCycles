#include "mainmenu.h"


MainMenu::MainMenu()
{
    numMaps = 1;

}

ref_ptr<Node> MainMenu::getMenuNode(){

	// A geometry node for our menu:
        ref_ptr<Geode> menuGeode = new  Geode();
       // Text instance that wil show up in the menu:
       ref_ptr<osgText::Text> textOne = new osgText::Text();

       // Set up geometry for the menu and add it to the menu
        ref_ptr<Geometry> menuBackgroundGeometry = new  Geometry();
        ref_ptr<Geometry> selector = new Geometry();

        //sets verticies of the menu
        ref_ptr<Vec3Array> menuBackgroundVertices = new  Vec3Array;
       menuBackgroundVertices->push_back( Vec3(0,    0,-1) );
       menuBackgroundVertices->push_back( Vec3(1024,  0,-1) );
       menuBackgroundVertices->push_back( Vec3(1024,768,-1) );
       menuBackgroundVertices->push_back( Vec3(  0,768,-1) );

        ref_ptr<DrawElementsUInt> menuBackgroundIndices =
          new  DrawElementsUInt(PrimitiveSet::POLYGON, 0);
       menuBackgroundIndices->push_back(0);
       menuBackgroundIndices->push_back(1);
       menuBackgroundIndices->push_back(2);
       menuBackgroundIndices->push_back(3);

        ref_ptr<Vec4Array> menucolors = new  Vec4Array;
       menucolors->push_back(Vec4(1.f,1.f,1.f,1.f));

        Vec2Array* texcoords = new  Vec2Array(4);
       (*texcoords)[0].set(0.0f,0.0f);
       (*texcoords)[1].set(1.0f,0.0f);
       (*texcoords)[2].set(1.0f,1.0f);
       (*texcoords)[3].set(0.0f,1.0f);

       menuBackgroundGeometry->setTexCoordArray(0,texcoords);
        selector->setTexCoordArray(0,texcoords);
        ref_ptr<Texture2D> selectTexture = new  Texture2D;
       selectTexture->setDataVariance(Object::DYNAMIC);

        ref_ptr<Texture2D> menuTexture = new  Texture2D;
       menuTexture->setDataVariance(Object::DYNAMIC);
        ref_ptr<Image> menuImage;
       menuImage = osgDB::readImageFile("../assets/images/title.png");
       menuTexture->setImage(menuImage);
        ref_ptr<Vec3Array> menunormals = new  Vec3Array;
       menunormals->push_back(Vec3(0.0f,0.0f,1.0f));
       menuBackgroundGeometry->setNormalArray(menunormals);
       menuBackgroundGeometry->setNormalBinding(Geometry::BIND_OVERALL);
       menuBackgroundGeometry->addPrimitiveSet(menuBackgroundIndices);
       menuBackgroundGeometry->setVertexArray(menuBackgroundVertices);
       menuBackgroundGeometry->setColorArray(menucolors);
       menuBackgroundGeometry->setColorBinding(Geometry::BIND_OVERALL);
        // selector->

       menuGeode->addDrawable(menuBackgroundGeometry);
        menuGeode->addDrawable(selector);
  // Create and set up a state set using the texture from above:
        ref_ptr<StateSet> menuStateSet = new  StateSet();
       menuGeode->setStateSet(menuStateSet);
       menuStateSet->
         setTextureAttributeAndModes(0,menuTexture, StateAttribute::ON);

       // For this state set, turn blending on (so alpha texture looks right)
       menuStateSet->setMode(GL_BLEND, StateAttribute::ON);

       // Disable depth testing so geometry is draw regardless of depth values
       // of geometry already draw.
       menuStateSet->setMode(GL_DEPTH_TEST, StateAttribute::OFF);
       menuStateSet->setRenderingHint( StateSet::TRANSPARENT_BIN );

  // Add the text (Text class is derived from drawable) to the geode:
       menuGeode->addDrawable(textOne );

//WHEN more maps are added, this is going to need changing
       // Set up the parameters for the text we'll add to the menu:
       textOne->setCharacterSize(20);
       //textOne->setFont("C:/WINDOWS/Fonts/impact.ttf");
       textOne->setText("Tunnel");
       textOne->setAxisAlignment(osgText::Text::SCREEN);
       textOne->setPosition( Vec3(330,340,-1) );
       textOne->setColor( Vec4(0, 0, 0, 1) );
       ref_ptr<osgText::Text> instructionText = new osgText::Text();
        instructionText->setCharacterSize(15);
       //textOne->setFont("C:/WINDOWS/Fonts/impact.ttf");
       instructionText->setText("Press 'e' To Play");
       instructionText->setAxisAlignment(osgText::Text::SCREEN);
       instructionText->setPosition( Vec3(310,110,-1) );
       instructionText->setColor( Vec4(0, 0, 0, 1) );
       menuGeode->addDrawable(instructionText );
	// Add the goede to the scene:
	return menuGeode;

}
