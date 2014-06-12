#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <map>
#include <string>
namespace osg {
	class Node;
};

class ResourceManager{
public:
	static ResourceManager* getInstance();

	void setDirectory(std::string);

	void preload(std::string);
	osg::Node* get(std::string);
	osg::Node* getTo(std::string);
private:
	ResourceManager();
	std::map<std::string, osg::Node*> resources;
	std::string directory;
};
#endif