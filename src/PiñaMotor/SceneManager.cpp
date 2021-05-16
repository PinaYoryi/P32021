#include "SceneManager.h"
#include "ResourceManager.h"

//PRUEBA
#include "ComponentFactoryRegistration.h"

#include "Transform.h"
#include "Renderer.h"
#include "Animation.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Light.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "BasicAI.h"

#include "LuaReader.h"

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

bool SceneManager::loadComponents()
{
	try {
		ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioListener>("audiolistener");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioSource>("audiosource");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Rigidbody>("rigidbody");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation>("animation");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera>("camera");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer>("renderer");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Light>("light");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform>("transform");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<BasicAI>("basicai");
	}
	catch (...) {

		return false;
	}
	return true;
}

Entity* SceneManager::getEntityByID(int id, bool all)
{
	Entity* ent = nullptr;
	auto it = _entities.begin();
	while (ent == nullptr && it != _entities.end()) {
		if ((*it)->getId() == id)
			ent = *it;
		++it;
	}

	if (all) {
		it = _permanentEntities.begin();
		while (ent == nullptr && it != _permanentEntities.end()) {
			if ((*it)->getId() == id)
				ent = *it;
			++it;
		}
	}
	return ent;
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

bool SceneManager::loadScene(std::string sceneName,bool all ) {
	deleteEntities(all);
	std::string path = ResourceManager::GetInstance()->scene(sceneName);
   
	readFile(path);
	return true;
}