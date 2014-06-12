#include "Bullet.h"

#include "Component.h"
#include "Scene.h"
#include "Ship.h"

Bullet::Bullet(){
	osg::PositionAttitudeTransform* bullet = (Component::getBullet())->asPositionAttitudeTransform();
	if(Scene::getInstance()->getShip() != NULL){
		bullet->setPosition(Scene::getInstance()->getShip()->getPosition());
		this->addChild(bullet);
		this->approachVelocity(Scene::getInstance()->getShip()->getDirection() * 20, 1);
	}
}
