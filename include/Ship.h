#ifndef SHIP
#define SHIP

#include "Entity.h"
class Tilt;
class Gun;

class Ship : public Entity{
public:
	Ship();
	void toggleGun();
	virtual void approachVelocity(osg::Vec3, double);
	osg::Vec3 getDirection();
private:
	Gun* gun;
	Tilt* pitch;
	Tilt* roll;
	Tilt* yaw;
};

#endif