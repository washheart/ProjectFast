#ifndef COMPONENT
#define COMPONENT

class Gun;

namespace osg{
	class Transform;
};

namespace Component{
	osg::Transform* getShip();
	osg::Transform* getBullet();
	osg::Transform* getStar();
	osg::Transform* getPlanet();
	osg::Transform* getEnemy();
	osg::Transform* getMenuBox();
	Gun* getGun();
};

#endif