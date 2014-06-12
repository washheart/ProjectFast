#include "Scene.h"

#include "Ship.h"
#include "Enemy.h"
#include "Star.h"
#include "Bound.h"
#include "ResourceManager.h"

#include <osg/Camera>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <cmath>
#include <osg/Image>
#include <osgDB/readFile>
#include <osg/Texture2D>
#include <osg/Texture>
#include <osg/LightSource>
#include <osg/StateSet>
#include <iostream>

#include "KeyboardEventHandler.hpp"

osg::Vec3 terminal = osg::Vec3(3, 3, 3);
int x = 0;
int z = 0;


Scene* Scene::getInstance(){
	static Scene* scene = new Scene();
	return scene;
}

void Scene::update(){
	while(!unadded.empty()){
		Entity* entity = unadded.front(); 
		root->addChild(entity);
		unadded.pop();
		if(entity->getDescription(0) == "enemy") {
			enemies.push_back(entity);
		}
		else if(entity->getDescription(0) == "star") {
			stars.push_back(entity);
		}
		else if(entity->getDescription(0) == "bullet") {
			bullets.push_back(entity);
		}
	}

	int width = 130; 
	int height = 100; 
	Bound* inner = new Bound(osg::Vec2(-width/2, height/2), width, height);
	Bound* outer = new Bound(osg::Vec2(-width * 2, height * 2), width * 4, height * 4);
	
	updateShip(inner);
	updateEnemies(inner);
	updateStars(outer, inner);

	
	cleanUp();
	resolveCollisions();
	removeEntities();
}


void Scene::updateShip(Bound* bound){
	osg::Vec3 position = ship->getPosition();
	double x = position.x();
	double z = position.z();
	const double x_buffer = 73; 
	const double z_buffer = 43; 
	if(x > x_buffer){
		x = x_buffer;
	}else if(x < -x_buffer){
		x = -x_buffer;
	}

	if(z > z_buffer){
		z = z_buffer;
	}else if(z < -z_buffer){
		z = -z_buffer;
	}

	ship->setPosition(osg::Vec3(x, position.y(), z));
}

void Scene::updateStars(Bound* outer, Bound* inner){
	osg::Vec2 location = Scene::getRandomLocation(outer);
	if(!inner->contains(location)){
		Star* star = new Star();
		star->addDescription("star");
		star->setPosition(osg::Vec3(location.x(), 1500.0, location.y()));
		addEntity(star);
	}
}

void Scene::updateEnemies(Bound* bound){
	osg::Vec2 location = Scene::getRandomLocation(bound);
	if(((int)location.x()) % 5 == 0){
		Enemy* enemy = new Enemy();
		enemy->addDescription("enemy");
		enemy->setPosition(osg::Vec3(location.x(), 1500.0, location.y()));

		// Makes textures working, I hope
		osg::Image *img_muster = osgDB::readImageFile("objects/ship2.jpg");
		osg::Texture2D* texture = new osg::Texture2D;
		texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		texture->setWrap(osg::Texture::WrapParameter::WRAP_S, osg::Texture::REPEAT);
		texture->setWrap(osg::Texture::WrapParameter::WRAP_T, osg::Texture::REPEAT);
		texture->setImage(img_muster);
		osg::StateSet *stateSet = enemy->getOrCreateStateSet();
		stateSet->ref();
		stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

		addEntity(enemy);
	}
}

// Removes objects that no longer will be seen
void Scene::cleanUp() {
	//Bullets
	while(!bullets.empty() && (bullets.front()->getPosition().y() > 9001)){
		Entity* entity = bullets.front();
		bullets.pop_front();
		root->removeChild(entity);
	}

	// Stars
	if(!stars.empty() && (stars.front()->getPosition().y() < 400)){
		osg::Node* object = stars.front();
		stars.pop_back();
		root->removeChild(object);
	}

	//Enemies
	while((!enemies.empty()) && (enemies.front()->getPosition().y() < -100)){
		Entity* entity = enemies.front();
		enemies.pop_front();
		root->removeChild(entity);
	} 
}

void Scene::resolveCollisions() {
    std::list<Entity*>::iterator iter;
	
	osg::BoundingSphereImpl<osg::Vec3> shipBS  = osg::BoundingSphereImpl<osg::Vec3>(ship->getBound().center(), 5);

	// Enemies are used in every collision
	for(iter = enemies.begin(); iter != enemies.end(); iter++) {
		Entity* enemy = (*iter);
		osg::BoundingSphereImpl<osg::Vec3> enemyBS  = osg::BoundingSphereImpl<osg::Vec3>(enemy->getBound().center(), 5);
		
		if(enemyBS.intersects(shipBS)){
			unremoved.push(ship);
		}
		
		// Resolves Bullet vs. Enemy
		std::list<Entity*>::iterator iterB;
		for(iterB = bullets.begin(); iterB != bullets.end(); iterB++) {
			Entity* bullet = (*iterB);
			osg::BoundingSphere bulletBS = bullet->getBound();
			if(enemyBS.intersects(bulletBS)){
				unremoved.push(enemy);
				unremoved.push(bullet);
			}
		}
	}
}

void Scene::removeEntities() {
	while(!unremoved.empty()) {
		Entity* entity = unremoved.front();
		unremoved.pop();
		if(entity != NULL){
			if(entity->getDescription(0) == "enemy") {
				enemies.remove(entity);
			}
			else if(entity->getDescription(0) == "bullet") {
				bullets.remove(entity);
			}else if(entity->getDescription(0) == "ship") {
				ship = 0;
				break;
			}
			root->removeChild(entity);
		}
	}
}

// Add an enemy into the queue of "need-to-add" and a filtered queue
void Scene::addEntity(Entity* entity){
	unadded.push(entity);
}

bool Scene::hasShip(){
	return ship != 0;
}

Ship* Scene::getShip() const{
	return ship;
}

Scene::Scene(){
	root = new osg::Group();
	
	ship = new Ship();
	ship->addDescription("ship");
	
	// Makes textures working, I hope
	osg::Image *img_muster = osgDB::readImageFile("objects/tron2.jpg");
	osg::Texture2D* texture = new osg::Texture2D;
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WrapParameter::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WrapParameter::WRAP_T, osg::Texture::REPEAT);
	texture->setImage(img_muster);
	osg::StateSet *stateSet = ship->getOrCreateStateSet();
	stateSet->ref();
	stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

	root->addChild(ship);

	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
	ls->getLight()->setPosition(osg::Vec4(0, -250, 100, 0));
	ls->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	ls->getLight()->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));
	ls->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	root->addChild(ls.get());
}

osg::Vec2 Scene::getRandomLocation(Bound* b) {
	int x = (rand() % b->width) + b->point.x();
	int y = (rand() % b->height) - b->point.y();
	return osg::Vec2(x,y);
}

// Game Keyboard Handler Functions
void quit() {
	exit(01);
}

void setZ(double velocity){
	Ship* ship = Scene::getInstance()->getShip();
	ship->approachVelocity(osg::Vec3(ship->getApproachVelocity().x(), ship->getApproachVelocity().y(), velocity), .08);
}
void moveZPositive() {
	setZ(terminal.z());
	z++;
}
void moveZNegative() {
	setZ(-terminal.z());
	z++;
}
void stopZPositive() {
	if(z > 1){
		z--;
		moveZNegative();
	} else {
		setZ(0);
	}

	z--;
}
void stopZNegative() {
	if(z > 1){
		z--;
		moveZPositive();
	} else {
		setZ(0);
	}

	z--;
}

void setX(double velocity){
	Scene* scene = Scene::getInstance();
	Ship* ship = scene->getShip();
	ship->approachVelocity(osg::Vec3(velocity, ship->getApproachVelocity().y(), ship->getApproachVelocity().z()), .08);
}
void moveXPositive() {
	setX(terminal.x());
	x++;
}
void moveXNegative() {
	setX(-terminal.x());
	x++;
}
void stopXPositive() {
	if(x > 1){
		x--;
		moveXNegative();
	} else {
		setX(0);
	}

	x--;
}
void stopXNegative() {
	if(x > 1){
		x--;
		moveXPositive();
	} else {
		setX(0);
	}

	x--;
}
void toggleShoot(){
	Scene::getInstance()->getShip()->toggleGun();
}

KeyboardEventHandler* Scene::createKeyHandler() {
	KeyboardEventHandler* keyHandler = new KeyboardEventHandler();
	
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Up, KeyboardEventHandler::KEY_DOWN, moveZPositive);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Up, KeyboardEventHandler::KEY_UP, stopZPositive);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Down, KeyboardEventHandler::KEY_DOWN, moveZNegative);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Down, KeyboardEventHandler::KEY_UP, stopZNegative);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Right, KeyboardEventHandler::KEY_DOWN, moveXPositive);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Right, KeyboardEventHandler::KEY_UP, stopXPositive);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Left, KeyboardEventHandler::KEY_DOWN, moveXNegative);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Left, KeyboardEventHandler::KEY_UP, stopXNegative);
	keyHandler->addFunction('z', KeyboardEventHandler::KEY_DOWN, toggleShoot);
	keyHandler->addFunction('z', KeyboardEventHandler::KEY_UP, toggleShoot);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Escape, KeyboardEventHandler::KEY_DOWN, quit);

	return keyHandler;
}

void Scene::attach(osgViewer::Viewer& viewer) const{
	double depth = 200;
	double height = 0;
	osg::Vec3 eye = osg::Vec3(0.0, -depth, height);
	osg::Vec3 at = osg::Vec3(0.0, 0.0, 0.0);
	osg::Vec3 up = osg::Vec3(0.0, height, depth);
	
	viewer.setSceneData(root);
	viewer.getEventHandlers().push_front(Scene::getInstance()->createKeyHandler()); 
	viewer.getCamera()->setViewMatrixAsLookAt(eye, at, up);
	viewer.getCamera()->setClearColor( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
}