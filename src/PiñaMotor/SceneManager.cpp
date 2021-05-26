#include "SceneManager.h"
#include "ResourceManager.h"
#include "BulletInstance.h"
#include "Gui.h"
#include "ComponentFactoryRegistration.h"

#include "Transform.h"
#include "Renderer.h"
#include "Animation.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Light.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "ImageComponent.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "BasicAI.h"
#include "SkyBox.h"

#include "LuaReader.h"

SceneManager* SceneManager::_singleton = nullptr;

SceneManager::~SceneManager() {
	for (Entity* e : _entities) if (e != nullptr) delete e;
	for (Entity* r : _entitiesToRemove) if (r != nullptr) delete r;
	for (Entity* l : _entitiesToLoad) if (l != nullptr) delete l;
}

SceneManager* SceneManager::GetInstance() {
	return _singleton;
}

bool SceneManager::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new SceneManager(); return true;
}

bool SceneManager::addEntity(Entity* ent) {
	auto it = find(_entities.begin(), _entities.end(), ent);
	if (it != _entities.end()) return false;
	it = find(_entitiesToLoad.begin(), _entitiesToLoad.end(), ent);
	if (it != _entitiesToLoad.end()) return false;

	_entitiesToLoad.push_back(ent); return true;
}

bool SceneManager::addEntityToRemove(Entity* ent) {
	auto it = find(_entities.begin(), _entities.end(), ent);
	if (it == _entities.end()) return false;

	_entitiesToRemove.push_back(*it);
	_entities.erase(it);
	return true;
}

bool SceneManager::loadComponents() {
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
		ComponentFactoryRegistrations::ComponentFactoryRegistration<SkyBox>("skybox");
        ComponentFactoryRegistrations::ComponentFactoryRegistration<ButtonComponent>("button");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<TextComponent>("text");
		ComponentFactoryRegistrations::ComponentFactoryRegistration<ImageComponent>("image");
	}
	catch (...) {

		return false;
	}
	return true;
}

Entity* SceneManager::getEntityByID(int id)
{
	Entity* ent = nullptr;
	auto it = _entities.begin();
	while (ent == nullptr && it != _entities.end()) {
		if ((*it)->getId() == id)
			ent = *it;
		++it;
	}

	if (ent == nullptr) {
		auto it = _entitiesToLoad.begin();
		while (ent == nullptr && it != _entitiesToLoad.end()) {
			if ((*it)->getId() == id)
				ent = *it;
			++it;
		}
	}
	return ent;
}

void SceneManager::removeEntities() {
	for (Entity* e : _entitiesToRemove) {
		if (e) delete e;
	}
	_entitiesToRemove.clear();
}

std::vector<Entity*>* SceneManager::getEntities() {
	return &_entities;
}

void SceneManager::deleteEntities() {
	for (Entity* e : _entities) {
		_entitiesToRemove.push_back(e);
	}
	for (Entity* e : _entitiesToLoad) {
		_entitiesToRemove.push_back(e);
	}
	_entities.clear();
	_entitiesToLoad.clear();
}

void SceneManager::newScene(std::string sceneName, bool continueBullet) {
	deleteEntities();
	if (continueBullet) {
		BulletInstance::GetInstance()->setPaused(false);
		Gui::GetInstance()->setMouseVisibility(false);
	}

	_sceneName = ResourceManager::GetInstance()->scene(sceneName);
	_newScene = true;
}

void SceneManager::loadEntities() {	
	if (_newScene) {
		readFile(_sceneName);
		_newScene = false;
	}

	for (Entity* e : _entitiesToLoad)
		_entities.push_back(e);
	_entitiesToLoad.clear();

}

void SceneManager::pauseScene() {
	for (Entity* e : _entities)	e->setPaused(true);
	BulletInstance::GetInstance()->setPaused(true);
}

void SceneManager::continueScene() {
	for (Entity* e : _entities) {
		if (e->isPaused())
			e->setPaused(false);
		else
			addEntityToRemove(e);
	}
	BulletInstance::GetInstance()->setPaused(false);

}
