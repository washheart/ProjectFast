#include "Component.h"
#include <osg/Transform>
#include <osg/PositionAttitudeTransform>
#include "ResourceManager.h"
#include "Gun.h"

osg::Transform* Component::getShip(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("ship");
	origin->addChild(model);

	return origin;
}
osg::Transform* Component::getMenuBox(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("menuBox");
	origin->addChild(model);

	return origin;
}

osg::Transform* Component::getEnemy(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("enemy");
	origin->addChild(model);

	return origin;
}

Gun* Component::getGun(){
	return new Gun();
}

osg::Transform* Component::getBullet(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("bullet");
	origin->addChild(model);

	return origin;
}

osg::Transform* Component::getStar(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("star");
	origin->addChild(model);
	return origin;
}

osg::Transform* Component::getPlanet(){
	osg::PositionAttitudeTransform* origin = new osg::PositionAttitudeTransform();
	osg::Node* model = ResourceManager::getInstance()->get("planet");
	origin->addChild(model);
	return origin;
}
