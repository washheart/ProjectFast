#include "Entity.h"

#include "Move.h"

Entity::Entity(){
	move = new Move();
	this->setUpdateCallback(move);
}

osg::Vec3 Entity::getApproachVelocity() {
	return move->getApproachVelocity();
}

osg::Vec3 Entity::getCurrentVelocity() {
	return move->getVelocity();
}

void Entity::approachVelocity(osg::Vec3 velocity, double rate) {
	move->approachVelocity(velocity, rate);
}