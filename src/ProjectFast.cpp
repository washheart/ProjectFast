
#include <osgViewer/Viewer>
#include <iostream>

#include "MainMenu.h"
#include "Scene.h"
#include "Ship.h"
#include "ResourceManager.h"



int main(){
	osgViewer::Viewer viewer;
	ResourceManager::getInstance()->setDirectory("objects/");
	
	// Start Menu
	MainMenu::getInstance()->attach(viewer);
	viewer.realize();
	while(MainMenu::inMenu){
		MainMenu::getInstance()->update();
		viewer.frame();
	}
	viewer.getEventHandlers().clear();
	
	// Game Loop
	Scene::getInstance()->attach(viewer);
	viewer.realize();

	while(!viewer.done() && Scene::getInstance()->hasShip()){
		Scene::getInstance()->update();
		viewer.frame();
	}
	viewer.getEventHandlers().clear();

	return 0;
}