//#include <iostream>
//
//#include <osg/Group>
//#include <osg/LightSource>
//#include <osg/Camera>
//#include <osg/Node>
//#include <osg/Material>
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgViewer/ViewerEventHandlers>
//
////#include "../include/KeyboardEventHandler.hpp"
////#include "../include/MotionCallbacks.hpp"
//
//using namespace std;
//
//// Nodes that need global references
////osg::ref_ptr<osg::Node> bike_frame_node;
////osg::ref_ptr<osg::Node> bike_handle_node;
////osg::ref_ptr<osg::Node> bike_wheel_node;
//
//// Global CallBacks
////osg::ref_ptr<MoveCallback> moveCB;
////osg::ref_ptr<TurnCallback> turnCB;
////osg::ref_ptr<SpinCallback> spinCB;
//
//// Functions used by keyboard handler to control animation
////void moveYUp() {
////	moveCB->setYIncr(0.1);
////	spinCB->spin(1.0);
////}
////void moveYDown() {
////	moveCB->setYIncr(-0.1);
////	spinCB->spin(-1.0);
////}
////
////void stopX() {
////	moveCB->setXIncr(0);
////	spinCB->spin(0.0);
////}
////void stopY() {
////	moveCB->setYIncr(0);
////	spinCB->spin(0.0);
////}
////
////void turn_left() {
////	turnCB->set_delta_rotation(0.1);
////}
////void turn_right() {
////	turnCB->set_delta_rotation(-0.1);
////}
////void stop_turn() {
////	turnCB->set_delta_rotation(0);
////}
//
//// Creates handler for keyboard events
////KeyboardEventHandler* createKeyHandler();
//
//// main function
//int main()
//{
//	// Create root node for scene graph
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// Read the obj files, and color them in.
//	/*osg::ref_ptr<osg::Node> bike_frame_node = osgDB::readNodeFile("objects/bike_frame.obj");
//	osg::ref_ptr<osg::Node> bike_handle_node = osgDB::readNodeFile("objects/bike_handle.obj");
//	osg::ref_ptr<osg::Node> bike_wheel_node = osgDB::readNodeFile("objects/bike_wheel.obj");*/
//	osg::ref_ptr<osg::Node> terrain_node = osgDB::readNodeFile("objects/Terrain2.obj");
//
//	/*osg::ref_ptr<osg::StateSet> frame_state = bike_frame_node->getOrCreateStateSet();
//	osg::ref_ptr<osg::StateSet> handle_state = bike_handle_node->getOrCreateStateSet();
//	osg::ref_ptr<osg::StateSet> wheel_state = bike_wheel_node->getOrCreateStateSet();*/
//	osg::ref_ptr<osg::StateSet> terrain_state = terrain_node->getOrCreateStateSet();
//	
//	//osg::ref_ptr<osg::Material> frame_mat = new osg::Material;
//	//osg::ref_ptr<osg::Material> handle_mat = new osg::Material;
//	//osg::ref_ptr<osg::Material> wheel_mat = new osg::Material;
//	osg::ref_ptr<osg::Material> terrain_mat = new osg::Material;
//	
//	/*frame_mat->setDiffuse(osg::Material::FRONT, osg::Vec4(0.6f, 0.2f, 0.0f, 1.0f));
//	frame_mat->setSpecular(osg::Material::FRONT, osg::Vec4(1.0f, 0.5f, 0.0f, 1.0f));
//	frame_mat->setShininess(osg::Material::FRONT, 128.0f);
//	frame_state->setAttribute(frame_mat.get());
//	
//	handle_mat->setDiffuse(osg::Material::FRONT, osg::Vec4(0.6f, 0.2f, 0.0f, 1.0f));
//	handle_mat->setSpecular(osg::Material::FRONT, osg::Vec4(1.0f, 0.5f, 0.0f, 1.0f));
//	handle_mat->setShininess(osg::Material::FRONT, 128.0f);
//	handle_state->setAttribute(handle_mat.get());
//	
//	wheel_mat->setDiffuse(osg::Material::FRONT, osg::Vec4(0.01f, 0.01f, 0.01f, 1.0f));
//	wheel_mat->setSpecular(osg::Material::FRONT, osg::Vec4(0.01f, 0.01f, 0.01f, 1.0f));
//	wheel_mat->setShininess(osg::Material::FRONT, 2.0f);
//	wheel_state->setAttribute(wheel_mat.get());*/
//
//	
//	
//	terrain_mat->setDiffuse(osg::Material::FRONT, osg::Vec4(0.2f, 0.2f, 0.25f, 1.0f));
//	/*
//	terrain_mat->setSpecular(osg::Material::FRONT, osg::Vec4(0.8f, 0.8f, 1.0f, 1.0f));
//	terrain_mat->setShininess(osg::Material::FRONT, 128.0f);
//	*/
//	terrain_state->setAttribute(terrain_mat.get());
//	
//
//	// Positioning Nodes
//	/*osg::ref_ptr<osg::PositionAttitudeTransform> positioning_back_node = new osg::PositionAttitudeTransform;
//	osg::ref_ptr<osg::PositionAttitudeTransform> positioning_frame_node = new osg::PositionAttitudeTransform;
//	osg::ref_ptr<osg::PositionAttitudeTransform> positioning_front_node = new osg::PositionAttitudeTransform;
//	*/
//	//positioning_frame_node->setPosition(osg::Vec3(0.0, 0.0, 0.0));
//	//positioning_front_node->setPosition(osg::Vec3(0.0, 7.2, 0.0));
//	//positioning_back_node->setPosition(osg::Vec3(0.0, -7.6, 0.0));
//
//	//// Restores the object to its original position
//	//osg::ref_ptr<osg::PositionAttitudeTransform> reposNode = new osg::PositionAttitudeTransform;
//	//reposNode->setPosition(osg::Vec3(0, 0, 2));
//	//reposNode->setScale(osg::Vec3(0.1, 0.1, 0.1));
//
//	// Create the transform nodes that will be animated
//	/*osg::ref_ptr<osg::PositionAttitudeTransform> turn_node = new osg::PositionAttitudeTransform;
//	osg::ref_ptr<osg::PositionAttitudeTransform> spin_node = new osg::PositionAttitudeTransform;
//	osg::ref_ptr<osg::PositionAttitudeTransform> move_node = new osg::PositionAttitudeTransform;*/
//	
//	/*moveCB = new MoveCallback;
//	turnCB = new TurnCallback;
//	spinCB = new SpinCallback;*/
//	
//	/*spin_node->setUpdateCallback(spinCB.get());
//	turn_node->setUpdateCallback(turnCB.get());
//	move_node->setUpdateCallback(moveCB.get());
//*/
//	// Constructs the heirarchy of the objects
//	/*spin_node->addChild(bike_wheel_node.get());
//	turn_node->addChild(spin_node.get());
//	turn_node->addChild(bike_handle_node.get());*/
//
//	/*positioning_back_node->addChild(spin_node.get());
//	positioning_frame_node->addChild(bike_frame_node.get());
//	positioning_front_node->addChild(turn_node.get());*/
//
//	/*reposNode->addChild(positioning_back_node.get());
//	reposNode->addChild(positioning_frame_node.get());
//	reposNode->addChild(positioning_front_node.get());*/
//
//	/*move_node->addChild(reposNode.get());*/
//
//	// Create a "distant" light source
//	osg::Vec3 lightDirection(1, -1, 1);
//	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
//	ls->getLight()->setPosition(osg::Vec4(lightDirection, 0));
//	ls->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
//	ls->getLight()->setDiffuse(osg::Vec4(1.0, 1.0, 0.7, 1.0));
//
//	//osgViewer::Viewer viewer = osgViewer::Viewer();
//	osgViewer::Viewer viewer;
//	// these handlers provide useful interactive functions
////	viewer.addEventHandler(new osgViewer::StatsHandler);
////	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
////	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
//	//KeyboardEventHandler* keyHandler = createKeyHandler();
//	//viewer.getEventHandlers().push_front(keyHandler); 
//
//	// set up manipulator to force camera to track BIKE
////	osg::ref_ptr<osgGA::NodeTrackerManipulator> manip = new osgGA::NodeTrackerManipulator;
////	manip->setTrackNode(bike_frame_node.get());
////	manip->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER);
////	viewer.setCameraManipulator(manip.get());
//	/*osg::Vec3d eye = osg::Vec3d(0, 0, 100);
//	osg::Vec3d center = osg::Vec3d(0, 0, 0);
//	osg::Vec3d up = osg::Vec3d(0, 1, 0);*/
//    viewer.getCamera()->setViewport(0, 0, 640, 480);
//	viewer.getCamera()->setProjectionMatrixAsPerspective(
//       45.0,
//       viewer.getCamera()->getViewport()->aspectRatio(),
//       0.1,
//       1000.0
//    );
//	viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3d(100.0, 0.0, 100.0), osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, -1.0, 0.0));
//    
//
//	// attach nodes to the root of the graph
//	root->addChild(terrain_node.get());
//	//root->addChild(move_node.get());
//	root->addChild(ls.get());
//
//	// prepare the scene for viewing
//	viewer.setSceneData(root.get());
//	viewer.realize();
//
//	// start the main event loop
//	return (viewer.run());
//}
//
///* Create and configure the keyboard input handler */
////KeyboardEventHandler* createKeyHandler() {
////	KeyboardEventHandler* keyHandler = new KeyboardEventHandler();
////	
////	keyHandler->addFunction('w', KeyboardEventHandler::KEY_DOWN, moveYUp);
////	keyHandler->addFunction('w', KeyboardEventHandler::KEY_UP, stopY);
////	keyHandler->addFunction('a', KeyboardEventHandler::KEY_DOWN, turn_left);
////	keyHandler->addFunction('a', KeyboardEventHandler::KEY_UP, stop_turn);
////	keyHandler->addFunction('s', KeyboardEventHandler::KEY_DOWN, moveYDown);
////	keyHandler->addFunction('s', KeyboardEventHandler::KEY_UP, stopY);
////	keyHandler->addFunction('d', KeyboardEventHandler::KEY_DOWN, turn_right);
////	keyHandler->addFunction('d', KeyboardEventHandler::KEY_UP, stop_turn);
////	
////	keyHandler->addFunction('q', KeyboardEventHandler::KEY_DOWN, turn_left);
////	keyHandler->addFunction('q', KeyboardEventHandler::KEY_UP, stop_turn);
////	keyHandler->addFunction('e', KeyboardEventHandler::KEY_DOWN, turn_right);
////	keyHandler->addFunction('e', KeyboardEventHandler::KEY_UP, stop_turn);
////
////	return keyHandler;
////}
