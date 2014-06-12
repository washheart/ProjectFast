#include "MainMenu.h"

#include "MenuBox.h"
#include "Planet.h"
#include "ResourceManager.h"
#include "Bound.h"

#include <osg/Camera>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Image>
#include <osgDB/readFile>
#include <osg/Texture2D>
#include <osg/Texture>
#include <osgText/Text>
#include <osg/StateSet>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <iostream>
#include "KeyboardEventHandler.hpp"

osg::Vec3 terminalMM = osg::Vec3(3, 3, 3);
int xMM = 0;
int zMM = 0;
bool MainMenu::inMenu = true;


MainMenu* MainMenu::getInstance(){
	static MainMenu* mainMenu = new MainMenu();
	return mainMenu;
}

void MainMenu::update(){
	while(!unadded.empty()){
		root->addChild(unadded.front());
		unadded.pop();
	}

	int width = 160; 
	int height = 100; 
	Bound* inner = new Bound(osg::Vec2(-width/2, height/2), width, height);
	Bound* outer = new Bound(osg::Vec2(-width * 2, height * 2), width * 4, height * 4);
	
	//updateMenuBox(inner);
	updatePlanets(outer, inner);
}

void MainMenu::updateMenuBox(Bound* bound){
	osg::Vec3 position = menuBox->getPosition();
	double xMM = position.x();
	double zMM = position.z();
	const double x_buffer = 73; 
	const double z_buffer = 43; 
	if(xMM > x_buffer){
		xMM = x_buffer;
	}else if(xMM < -x_buffer){
		xMM = -x_buffer;
	}

	if(zMM > z_buffer){
		zMM = z_buffer;
	}else if(zMM < -z_buffer){
		zMM = -z_buffer;
	}

	menuBox->setPosition(osg::Vec3(xMM, position.y(), zMM));
}

void MainMenu::updatePlanets(Bound* outer, Bound* inner){
	planetCounter++;
	if(planetCounter >= 25) {
		osg::Vec2 location = MainMenu::getRandomLocation(outer);
		if(!inner->contains(location)){
			Planet* planet = new Planet();
			planet->useShader();
			planet->setPosition(osg::Vec3(location.x(), 1000.0, location.y()));
			addEntity(planet);
		}
		// Removes  planets that no longer will be seen/used
		if(unremoved.front()->getPosition().y() < -200){
			osg::Node *planet = unremoved.front();
			unremoved.pop();
			root->removeChild(planet);
		}
		planetCounter = 0;
	}
}

void MainMenu::addEntity(Entity* entity){
	unadded.push(entity);
	unremoved.push(entity);
}

MenuBox* MainMenu::getMenuBox() const{
	return menuBox;
}

MainMenu::MainMenu(){
	root = new osg::Group();
	planetCounter = 0;

	menuBox = new MenuBox();
	menuBox->setPosition(osg::Vec3(0.0, -100.0, 0.0));

	root->addChild(menuBox);
	osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
	
	pat->setPosition(osg::Vec3(0,-180, 0));
	osg::Geode* geode_asdf = new osg::Geode();
	osg::Sphere* sphere = new osg::Sphere();
	osg::ShapeDrawable* shape = new osg::ShapeDrawable(sphere); 
	//geode_asdf->addDrawable(shape);
	osgText::Text* text_asdf = new osgText::Text();
	std::string font("fonts/arial.ttf");

	geode_asdf->addDrawable(text_asdf);
	text_asdf->setFont(font);
	text_asdf->setCharacterSize(40);
	text_asdf->setRotation(osg::Quat(-90 * 1.07, osg::Vec3(0, 0, 1)));
	text_asdf->setAlignment(osgText::TextBase::AlignmentType::RIGHT_BASE_LINE);
	text_asdf->setText("Arrow Keys to Move\n");
	pat->addChild(geode_asdf);
	root->addChild(pat);
}

osg::Vec2 MainMenu::getRandomLocation(Bound* b) {
	int x = (rand() % b->width) + b->point.x();
	int y = (rand() % b->height) - b->point.y();
	return osg::Vec2(x,y);
}

// Menu Keyboard Handler Functions
void startGame(){
	MainMenu::inMenu = false;
}
void quitMM() {
	exit(01);
}

void setZMM(double velocity){
	MenuBox* menuBox = MainMenu::getInstance()->getMenuBox();
	menuBox->approachVelocity(osg::Vec3(menuBox->getApproachVelocity().x(), menuBox->getApproachVelocity().y(), velocity), .08);
}
void moveZPositiveMM() {
	setZMM(terminalMM.z());
	zMM++;
}
void moveZNegativeMM() {
	setZMM(-terminalMM.z());
	zMM++;
}
void stopZPositiveMM() {
	if(zMM > 1){
		zMM--;
		moveZNegativeMM();
	} else {
		setZMM(0);
	}

	zMM--;
}
void stopZNegativeMM() {
	if(zMM > 1){
		zMM--;
		moveZPositiveMM();
	} else {
		setZMM(0);
	}

	zMM--;
}

void setXMM(double velocity){
	MainMenu* mainMenu = MainMenu::getInstance();
	MenuBox* menuBox = mainMenu->getMenuBox();
	menuBox->approachVelocity(osg::Vec3(velocity, menuBox->getApproachVelocity().y(), menuBox->getApproachVelocity().z()), .08);
}
void moveXPositiveMM() {
	setXMM(terminalMM.x());
	xMM++;
}
void moveXNegativeMM() {
	setXMM(-terminalMM.x());
	xMM++;
}
void stopXPositiveMM() {
	if(xMM > 1){
		xMM--;
		moveXNegativeMM();
	} else {
		setXMM(0);
	}

	xMM--;
}
void stopXNegativeMM() {
	if(xMM > 1){
		xMM--;
		moveXPositiveMM();
	} else {
		setXMM(0);
	}

	xMM--;
}

KeyboardEventHandler* MainMenu::createKeyHandler() {
	KeyboardEventHandler* keyHandler = new KeyboardEventHandler();
	
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Up, KeyboardEventHandler::KEY_DOWN, moveZPositiveMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Up, KeyboardEventHandler::KEY_UP, stopZPositiveMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Down, KeyboardEventHandler::KEY_DOWN, moveZNegativeMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Down, KeyboardEventHandler::KEY_UP, stopZNegativeMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Right, KeyboardEventHandler::KEY_DOWN, moveXPositiveMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Right, KeyboardEventHandler::KEY_UP, stopXPositiveMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Left, KeyboardEventHandler::KEY_DOWN, moveXNegativeMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Left, KeyboardEventHandler::KEY_UP, stopXNegativeMM);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Return, KeyboardEventHandler::KEY_UP, startGame);
	keyHandler->addFunction(osgGA::GUIEventAdapter::KEY_Escape, KeyboardEventHandler::KEY_DOWN, quitMM);

	return keyHandler;
}

void MainMenu::attach(osgViewer::Viewer& viewer) const{
	double depth = 200;
	double height = 0;
	osg::Vec3 eye = osg::Vec3(0.0, -depth, height);
	osg::Vec3 at = osg::Vec3(0.0, 0.0, 0.0);
	osg::Vec3 up = osg::Vec3(0.0, height, depth);
	
	viewer.setSceneData(root);
	viewer.getEventHandlers().push_front(MainMenu::getInstance()->createKeyHandler()); 
	viewer.getCamera()->setViewMatrixAsLookAt(eye, at, up);
	viewer.getCamera()->setClearColor( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
}