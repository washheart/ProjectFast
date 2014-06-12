#ifndef SCENE
#define SCENE

#include <queue>
#include <list>
#include <osg/Vec2>

namespace osg{
	class Group;
}
namespace osgViewer{
	class Viewer;
};
class Bound;
class Ship;
class Star;
class Entity;
class KeyboardEventHandler;

class Scene{
public:
	static Scene* getInstance();

	void attach(osgViewer::Viewer&) const;
	void update();
	void addEntity(Entity* entity);
	bool hasShip();
	Ship* getShip() const;
protected:
private:
	Scene();
	Scene(const Scene&);
	KeyboardEventHandler* createKeyHandler();

	osg::Group* root;
	static osg::Vec2 getRandomLocation(Bound* b);

	void addEntities();
	void updateStars(Bound*, Bound*);
	void updateShip(Bound*);
	void updateEnemies(Bound*);
	void cleanUp();
	void resolveCollisions();
	void removeEntities();
	
	std::queue<Entity*> unadded;
	std::queue<Entity*> unremoved;
	std::list<Entity*> enemies;
	std::list<Entity*> stars;
	std::list<Entity*> bullets;
	Ship* ship;
};

#endif