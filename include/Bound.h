#ifndef BOUND
#define BOUND

#include <osg/Vec2>

class Bound{
public:
	Bound(osg::Vec2, int, int);
	bool contains(osg::Vec2);
	
	osg::Vec2 point;
	int width; 
	int height; 
};

#endif