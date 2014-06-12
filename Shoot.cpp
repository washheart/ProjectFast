#include "Shoot.h"

#include "Scene.h"
#include "Ship.h"
#include "Bullet.h"

Shoot::Shoot(){
	this->isFiring = false;
	this->reload = 1;
}

void Shoot::operator() (osg::Node* n, osg::NodeVisitor* nv){
	if(isFiring){
		reload--;
		if(reload == 0){
			Bullet* bullet = new Bullet();
			bullet->addDescription("bullet");
			Scene::getInstance()->addEntity(bullet);
			reload = 3;
		}
	}

	traverse(n,nv);
}

void Shoot::toggle(){
	isFiring = !isFiring;
	reload = 1; 
}