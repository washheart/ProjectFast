#ifndef ENTITY
#define ENTITY

#include <osg/PositionAttitudeTransform>
class Move;

class Entity : public osg::PositionAttitudeTransform{
public:
	Entity();
	osg::Vec3 getApproachVelocity();
	osg::Vec3 getCurrentVelocity();
	virtual void approachVelocity(osg::Vec3, double);
private: 
	Move* move;
};

#endif