#include "Entity.h"
#include "ComponentFactory.h"
#include <map>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "LuaReader.h"
#include "SceneManager.h"

Entity::Entity() : _name("Entity"), _id(), _tag("Default")
{
	
}

Entity::Entity(std::string entityName, int id, std::string entityTag) : _name(entityName), _tag(entityTag), _id(id)
{
}

Entity::~Entity() {

}

void Entity::init()
{
	int i = 0;
	int numComponents = compUnique.size();
	int initedComps = 0;
	while (initedComps != numComponents) {
		if (!compinits[i] && compUnique[i]->init(compMaps[i])) {
			++initedComps;
			compinits[i] = true;
		}
		++i;
		i %= numComponents;
	}
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

Entity* Entity::instantiate(std::string file)
{
	std::string path = ResourceManager::GetInstance()->prefab(file);
	Entity* ent = readPrefab(path);
	SceneManager::GetInstance()->addEntity(ent);
	return ent;
}
