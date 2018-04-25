#include "ResourceManager.h"
#include <osg/Node>
#include <osgDB/ReadFile>

ResourceManager::ResourceManager() : directory(){}

ResourceManager* ResourceManager::getInstance() {
	static ResourceManager* instance = new ResourceManager();
	return instance;
}

void ResourceManager::setDirectory(std::string directory){
	this->directory = directory;
}

void ResourceManager::preload(std::string resource){
	osg::Node* node = osgDB::readNodeFile(directory + resource + ".obj");
	if (node != nullptr){
		node->addDescription(resource);
		resources[directory + resource] = node; 
	}
}

osg::Node* ResourceManager::getTo(std::string resource){
	osg::Node* node = osgDB::readNodeFile(directory + resource + ".osg");
	node->addDescription(resource);
	resources[directory + resource] = node; 
	return node;
}

osg::Node* ResourceManager::get(std::string resource){
	osg::Node* node = resources[directory + resource]; 
	if(node != NULL){
		return node;
	}
	
	preload(resource);
	return resources[directory + resource];
}