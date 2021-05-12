#include "Entity.h"
#include "ComponentFactory.h"
#include <map>
#include "SceneManager.h"

Entity::Entity() : _name("Entity"), _tag("Deafult")
{
	addComponent<Transform>(std::map<std::string,std::string>());
	
}

Entity::Entity(std::string entityName) : _name(entityName), _tag("Deafult")
{
	addComponent<Transform>();
}

Entity::Entity(std::string entityName, std::string entityTag) : _name(entityName), _tag(entityTag)
{
}

Entity::~Entity() {

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