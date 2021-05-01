#include "Entity.h"
#include "ComponentFactory.h"
#include <map>
#include "Transform.h"


Entity::Entity() : _name("Entity"), _id()
{
	
}

Entity::Entity(char* entityName, int id) : _name(entityName), _id(id)
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