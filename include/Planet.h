#ifndef PLANET
#define PLANET

#include "Entity.h"
class Move;

class Planet : public Entity{
public:
	Planet();
	void useShader();
private:
	bool loadShaderSource(osg::Shader* obj, const std::string& fileName);
};

#endif