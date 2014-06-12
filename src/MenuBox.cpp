#include "MenuBox.h"
#include "Tilt.h"
#include "Component.h"
#include <osg/Shader>
#include <osg/Program>
#include <iostream>

MenuBox::MenuBox(){
	pitch2 = new Tilt(osg::Vec3(1,0,0));
	roll2 = new Tilt(osg::Vec3(0,1,0));
	yaw2 = new Tilt(osg::Vec3(0,0,1));

	osg::PositionAttitudeTransform* menuBox = (Component::getMenuBox())->asPositionAttitudeTransform();
	menuBox->setAttitude(osg::Quat(std::atan(1.0) * 2, osg::Vec3(0,0,1)));
	
	
	osg::PositionAttitudeTransform* yaw_node2 = new osg::PositionAttitudeTransform();
	yaw_node2->addChild(menuBox);
	yaw_node2->setUpdateCallback(yaw2);
	
	osg::PositionAttitudeTransform* roll_node2 = new osg::PositionAttitudeTransform();
	roll_node2->addChild(yaw_node2);
	roll_node2->setUpdateCallback(roll2);

	osg::PositionAttitudeTransform* pitch_node2 = new osg::PositionAttitudeTransform();
	pitch_node2->addChild(roll_node2);
	pitch_node2->setUpdateCallback(pitch2);
	
	this->addChild(pitch_node2);
}

void MenuBox::useShader() {
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

bool MenuBox::loadShaderSource(osg::Shader* obj, const std::string& fileName) {
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

void MenuBox::approachVelocity(osg::Vec3 velocity, double rate){
//	Entity::approachVelocity(velocity, rate);
	roll2->approachRotation(velocity.x() * .03, rate);
	yaw2->approachRotation(-velocity.x() * .03, rate);
	pitch2->approachRotation(velocity.z() * .03, rate);
}

osg::Vec3 MenuBox::getDirection(){
	osg::Vec3 direction = this->getCurrentVelocity();
	direction.set(direction.x(), 15, direction.z());
	direction.normalize();
	return direction;
}