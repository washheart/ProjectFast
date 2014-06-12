#ifndef MENUBOX
#define MENUBOX

#include "Entity.h"
class Tilt;

class MenuBox : public Entity{
public:
	MenuBox();
	virtual void approachVelocity(osg::Vec3, double);
	osg::Vec3 getDirection();
	void useShader();
	bool loadShaderSource(osg::Shader* obj, const std::string& fileName);
private:
	Tilt* pitch2;
	Tilt* roll2;
	Tilt* yaw2;
};

#endif