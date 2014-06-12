#ifndef MAINMENU
#define MAINMENU

#include <queue>
#include <osg/Vec2>

namespace osg{
	class Group;
}
namespace osgViewer{
	class Viewer;
};
class Bound;
class MenuBox;
class Star;
class Entity;
class KeyboardEventHandler;

class MainMenu{
public:
	static MainMenu* getInstance();
	static bool inMenu;

	void attach(osgViewer::Viewer&) const;
	void update();
	void addEntity(Entity* entity);
	
	MenuBox* getMenuBox() const;
private:
	MainMenu();
	MainMenu(const MainMenu&);
	KeyboardEventHandler* createKeyHandler();

	osg::Group* root;
	static osg::Vec2 getRandomLocation(Bound* b);

	void addEntities();
	void updatePlanets(Bound*, Bound*);
	void updateMenuBox(Bound*);
	
	std::queue<Entity*> unadded;
	std::queue<Entity*> unremoved;
	MenuBox* menuBox;

	int planetCounter;
};

#endif