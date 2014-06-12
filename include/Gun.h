#ifndef GUN
#define GUN

#include <osg/PositionAttitudeTransform>
class Shoot;

class Gun : public osg::PositionAttitudeTransform{
public:
	Gun();

	void toggle();
private:
	Shoot* shoot;
};

#endif