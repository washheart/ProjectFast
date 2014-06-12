#include "Planet.h"

#include "Component.h"
#include "Scene.h"

#include <osg/Material>
#include <osg/Shader>
#include <osg/Program>
#include <iostream>

Planet::Planet(){
	this->addChild(Component::getPlanet());
	this->approachVelocity(osg::Vec3(0.0, -2.0, 0.0), 1);
}

void Planet::useShader() {
	osg::StateSet* state = this->getOrCreateStateSet();

	osg::Program* colorProgram = new osg::Program;
	osg::Shader* starVertexObject = 
		new osg::Shader( osg::Shader::VERTEX );
	osg::Shader* starFragmentObject = 
		new osg::Shader( osg::Shader::FRAGMENT );
	colorProgram->addShader( starFragmentObject );
	colorProgram->addShader( starVertexObject );
	loadShaderSource(starVertexObject, "shaders/swizzle.vert");
	loadShaderSource(starFragmentObject, "shaders/swizzle.frag");

	state->setAttributeAndModes(colorProgram, osg::StateAttribute::ON);
}

bool Planet::loadShaderSource(osg::Shader* obj, const std::string& fileName) {
	if( fileName.length() == 0 )
	{
		std::cout << "File \"" << fileName << "\" not found." << std::endl;
		return false;
	}
	bool success = obj->loadShaderSourceFromFile( fileName.c_str());
	if ( !success  )
	{
		std::cout << "Couldn't load file: " << fileName << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}