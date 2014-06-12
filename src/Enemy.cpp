#include "Enemy.h"
#include "Tilt.h"
#include "Component.h"

Enemy::Enemy(){
	pitch = new Tilt(osg::Vec3(1,0,0));
	roll = new Tilt(osg::Vec3(0,1,0));
	yaw = new Tilt(osg::Vec3(0,0,1));

	osg::PositionAttitudeTransform* enemy = (Component::getEnemy())->asPositionAttitudeTransform();
	enemy->setAttitude(osg::Quat(std::atan(1.0) * -2, osg::Vec3(0,0,1)));
	
	
	osg::PositionAttitudeTransform* yaw_node = new osg::PositionAttitudeTransform();
	yaw_node->addChild(enemy);
	yaw_node->setUpdateCallback(yaw);
	
	osg::PositionAttitudeTransform* roll_node = new osg::PositionAttitudeTransform();
	roll_node->addChild(yaw_node);
	roll_node->setUpdateCallback(roll);

	osg::PositionAttitudeTransform* pitch_node = new osg::PositionAttitudeTransform();
	pitch_node->addChild(roll_node);
	pitch_node->setUpdateCallback(pitch);
	
	this->addChild(pitch_node);
	approachVelocity(osg::Vec3(0,-5,0), 1);
}

void Enemy::approachVelocity(osg::Vec3 velocity, double rate){
	Entity::approachVelocity(velocity, rate);
	roll->approachRotation(velocity.x() * .08, rate);
	yaw->approachRotation(-velocity.x() * .08, rate);
	pitch->approachRotation(velocity.z() * .08, rate);
}

