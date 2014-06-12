#ifndef SHOOT
#define SHOOT

#include <osg/NodeCallback>

class Shoot : public osg::NodeCallback{
public:
	Shoot();
	virtual void operator() (osg::Node*, osg::NodeVisitor*);
	void toggle();
private:
	bool isFiring; 
	int reload;
};

#endif