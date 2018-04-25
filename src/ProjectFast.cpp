
#include <osgViewer/Viewer>
#include <iostream>
#include <osgDB/Registry>

#include "MainMenu.h"
#include "Scene.h"
#include "Ship.h"
#include "ResourceManager.h"

USE_GRAPHICSWINDOW();  // ����޷��ҵ����ڵ�����
USE_OSGPLUGIN(obj)     // ��Ӷ�obj�ļ��Ľ���֧��

#ifdef _DEBUG //Ҳ���ܻᶨ��ΪDEBUG
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