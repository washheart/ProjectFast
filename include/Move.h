#ifndef MOVE
#define MOVE

#include <osg/NodeCallback>
#include <osg/Vec3>

namespace osg{
	class Node; 
	class NodeVisitor;
};

class Move : public osg::NodeCallback{
public:
	Move();
	virtual void operator() (osg::Node*, osg::NodeVisitor*);
	
	void approachVelocity(osg::Vec3, double);
	osg::Vec3 getVelocity();
	osg::Vec3 getApproachVelocity();
private: 
	osg::Vec3 approach;
	osg::Vec3 velocity;
	double rateOfAcceleration;
};

#endif