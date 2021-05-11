#include "SceneManager.h"
#include "ResourceManager.h"

//PRUEBA
#include "ComponentFactoryRegistration.h"

#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreColourValue.h>
#include <OgreLight.h>

#include "Transform.h"
#include "Renderer.h"
#include "Animation.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Light.h"
#include "LuaReader.h"

#include "PlayerController.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "Lifetime.h"


SceneManager* SceneManager::_singleton = nullptr;

SceneManager::~SceneManager() {
    deleteEntities(true);
}

SceneManager* SceneManager::GetInstance() {
	return _singleton;
}

bool SceneManager::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new SceneManager(); return true;
}

bool SceneManager::addEntity(Entity* ent, bool permanent) {
	std::vector<Entity*>* vec = &_entities;
	if (permanent) vec = &_permanentEntities;
	auto it = find(vec->begin(), vec->end(), ent);
	if (it != vec->end()) return false;
	vec->push_back(ent); return true;
}

bool SceneManager::removeEntity(Entity* ent, bool permanent) {
	std::vector<Entity*>* vec = &_entities;
	if (permanent) vec = &_permanentEntities;
	auto it = find(vec->begin(), vec->end(), ent);
	if (it == vec->end()) return false;
    delete *it;
	vec->erase(it);
}

std::vector<Entity*> SceneManager::getEntities() {
	std::vector<Entity*> list;
	list.reserve(_entities.size() + _permanentEntities.size());
	list.insert(list.end(), _entities.begin(), _entities.end());
	list.insert(list.end(), _permanentEntities.begin(), _permanentEntities.end());
	return list;
}

void SceneManager::deleteEntities(bool all) {
    for (Entity* e : _entities) delete e;
    if (all) for (Entity* p : _permanentEntities) delete p;
}

bool SceneManager::loadScene(std::string sceneName) {
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Lifetime> cpm7("lifetime");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioListener> cpm6("audiolistener");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioSource> cpm54("audiosource");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Rigidbody> cpm44("rigidbody");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<PlayerController> cpm5("playercontroller");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm4("animation");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cp3("camera");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2("renderer");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Light> cpl("light");
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm("transform");
	readFile();
    return true;
}