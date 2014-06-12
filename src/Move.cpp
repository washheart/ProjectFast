#include "Move.h"

#include <math.h>
#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/NodeVisitor>

Move::Move() : velocity(0,0,0), approach(0,0,0), rateOfAcceleration(0){}

void Move::operator() (osg::Node* n, osg::NodeVisitor* nv){
	osg::Vec3 delta = (approach - velocity) * rateOfAcceleration;
	
	double x, y, z;
	double buffer = .001;
	if(abs(delta.x()) < buffer){
		x = approach.x();
	}else x = delta.x() + velocity.x();

	if(abs(delta.y()) < buffer){
		y = approach.y();
	}else y = delta.y() + velocity.y();

	if(abs(delta.z()) < buffer){
		z = approach.z();
	}else z = delta.z() + velocity.z();

	velocity = osg::Vec3(x,y,z);

	osg::ref_ptr<osg::PositionAttitudeTransform> node = dynamic_cast<osg::PositionAttitudeTransform*>(n);
	node->setPosition(node->getPosition() + velocity);

	traverse(n,nv);
}

osg::Vec3 Move::getVelocity(){
	return velocity;
}

osg::Vec3 Move::getApproachVelocity(){
	return approach;
}

void Move::approachVelocity(osg::Vec3 approach, double rateOfAcceleration){
	this->approach = approach;
	this->rateOfAcceleration = rateOfAcceleration;
}