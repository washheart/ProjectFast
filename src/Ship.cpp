#include "Ship.h"
#include "Tilt.h"
#include "Component.h"
#include "Gun.h"

Ship::Ship(){
	pitch = new Tilt(osg::Vec3(1,0,0));
	roll = new Tilt(osg::Vec3(0,1,0));
	yaw = new Tilt(osg::Vec3(0,0,1));

	osg::PositionAttitudeTransform* ship = (Component::getShip())->asPositionAttitudeTransform();
	ship->setAttitude(osg::Quat(std::atan(1.0) * 2, osg::Vec3(0,0,1)));
	
	gun = Component::getGun();
	
	osg::PositionAttitudeTransform* yaw_node = new osg::PositionAttitudeTransform();
	yaw_node->addChild(ship);
	yaw_node->addChild(gun);
	yaw_node->setUpdateCallback(yaw);
	
	osg::PositionAttitudeTransform* roll_node = new osg::PositionAttitudeTransform();
	roll_node->addChild(yaw_node);
	roll_node->setUpdateCallback(roll);

	osg::PositionAttitudeTransform* pitch_node = new osg::PositionAttitudeTransform();
	pitch_node->addChild(roll_node);
	pitch_node->setUpdateCallback(pitch);
	
	this->addChild(pitch_node);
}

void Ship::toggleGun(){
	gun->toggle();
}

void Ship::approachVelocity(osg::Vec3 velocity, double rate){
	Entity::approachVelocity(velocity, rate);
	roll->approachRotation(velocity.x() * .08, rate);
	yaw->approachRotation(-velocity.x() * .08, rate);
	pitch->approachRotation(velocity.z() * .08, rate);
}

osg::Vec3 Ship::getDirection(){
	osg::Vec3 direction = this->getCurrentVelocity();
	direction.set(direction.x(), 15, direction.z());
	direction.normalize();
	return direction;
}