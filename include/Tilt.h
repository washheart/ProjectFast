#ifndef TILT
#define TILT

#include <osg/Vec3>
#include <osg/NodeCallback>
class osg::Node;
class osg::NodeVisitor;

class Tilt : public osg::NodeCallback{
public:
	Tilt(osg::Vec3);
	virtual void operator() (osg::Node*, osg::NodeVisitor*);
	double getRotation();
	void approachRotation(double, double);
private: 	
	double approach;
	double rate;		
	double rotation;
	
	osg::Vec3 axis;
};

#endif