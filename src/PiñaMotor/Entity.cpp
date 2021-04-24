#include "Entity.h"
#include "ComponentFactory.h"
#include <map>
#include "Transform.h"


Entity::Entity() : _name("Entity")
{
	addComponent<Transform>(std::map<std::string,std::string>());
	
}

Entity::Entity(char* entityName) : _name(entityName)
{
	addComponent<Transform>();
}

Entity::~Entity() {

}

void Entity::update() {
	for (auto& c : compUnique) {
		if (c) c->update();
	}
}

void Entity::render() {
	for (auto& c : compUnique) {
		 c->render();
	}
}