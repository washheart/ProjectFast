#include "Tilt.h"

#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/NodeVisitor>

Tilt::Tilt(osg::Vec3 axis) : rotation(0), approach(0), rate(0){
	this->axis = axis;
}

void Tilt::operator() (osg::Node* n, osg::NodeVisitor* nv){
	double delta = (approach - rotation) * rate;
	
	double buffer = .001;	
	if(abs(delta) < buffer){
		rotation = approach;
	} else {
		rotation += delta;
	}

	osg::ref_ptr<osg::PositionAttitudeTransform> node = dynamic_cast<osg::PositionAttitudeTransform*>(n);
	node->setAttitude(osg::Quat(rotation, axis));

	traverse(n,nv);
}

double Tilt::getRotation(){
	return rotation;
}

void Tilt::approachRotation(double rotation, double rate){
	this->approach = rotation;
	this->rate = rate;
}