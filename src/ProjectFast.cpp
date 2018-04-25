
#include <osgViewer/Viewer>
#include <iostream>
#include <osgDB/Registry>

#include "MainMenu.h"
#include "Scene.h"
#include "Ship.h"
#include "ResourceManager.h"

USE_GRAPHICSWINDOW();  // 解决无法找到窗口的问题
USE_OSGPLUGIN(obj)     // 添加对obj文件的解析支持

#ifdef _DEBUG //也可能会定义为DEBUG
	#pragma comment(lib, "osgdb_objd.lib" )
#else
	#pragma comment(lib, "osgdb_obj.lib" )
#endif

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