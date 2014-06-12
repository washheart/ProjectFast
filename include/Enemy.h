#ifndef ENEMY
#define ENEMY

#include "Entity.h"
class Tilt;

class Enemy : public Entity{
public:
	Enemy();
	virtual void approachVelocity(osg::Vec3, double);
private:
	Tilt* pitch;
	Tilt* roll;
	Tilt* yaw;
};

#endif