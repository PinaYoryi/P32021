#include "Entity.h"
#include "ComponentFactory.h"
#include <map>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "LuaReader.h"
#include "SceneManager.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Transform.h"

Entity::Entity() : _name("Entity"), _id(), _tag("Default"), _paused(false)
{

}

Entity::Entity(std::string entityName, int id, std::string entityTag) : _name(entityName), _tag(entityTag), _id(id), _paused(false)
{
}

Entity::~Entity() {

}

bool Entity::init()
{
	_numTriesToLoad = compUnique.size() * 10;
	int i = 0, j = 0;
	int numComponents = compUnique.size();
	int initedComps = 0;
	while (initedComps != numComponents && j<_numTriesToLoad) {
		if (!compinits[i] && compUnique[i]->init(compMaps[i])) {
			++initedComps;
			compinits[i] = true;
		}
		if (_needsOtherEntity) {
			return false;
		}
		++i;
		j++;
		i %= numComponents;
	}
	if (j >= _numTriesToLoad) {
	
		throw std::exception("Error al iniciar los componentes en Entity \n ");
	}
	Transform* t;
	i = 0;
	while (i < compUnique.size() && !dynamic_cast<Transform*> (compUnique[i].get()) ) {
		i++;
	}
	if (i!=0 && i < compUnique.size()) {		
		compUnique[0].swap(compUnique[i]);
	}
	return true;
}

void Entity::update() {
	for (auto& c : compUnique) {
		if (c) c->update();
	}

}

void Entity::fixedUpdate() {
	for (auto& c : compUnique) {
		if (c) c->fixedUpdate();
	}
}

void Entity::render() {
	for (auto& c : compUnique) {
		c->render();
	}
}

Entity* Entity::instantiate(std::string file, Vector3<> position, Quaternion rotation)
{
	std::string path = ResourceManager::GetInstance()->prefab(file);
	Entity* ent = readPrefab(path);
	ent->getComponent<Transform>()->setPosition(position);
	ent->getComponent<Transform>()->setRotation(rotation);
	SceneManager::GetInstance()->addEntity(ent);
	return ent;
}
