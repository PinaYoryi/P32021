#include "Entity.h"

Entity::Entity() : name("Entity")
{

}

Entity::Entity(char* entityName) : name(entityName)
{

}

Entity::~Entity() {

}

template<typename T, typename ...TArgs>
T* Entity::addComponent(TArgs ...args)
{
	T* t(new T(std::forward<TArgs>(args)...));
	std::unique_ptr<Component> c(t);
	//compUnique.push_back(std::move(c));	//¿Cómo funciona esto?
	componentsArray_[t->getID()] = t;
	return t;
}

template<typename T>
T* Entity::getComponent(ecs::CmpIdType id)
{
	return compArray[id];
}

bool Entity::hasComponent(ecs::CmpIdType id) 
{
	return compArray[id];
}

template<typename T>
T* Entity::removeComponent(ecs::CmpIdType id) 
{
	//¿Quitar de unique pointers?
	T* save = compArray[id];
	compArray[id] = nullptr;
	return save;
};

void Entity::update() {
	for (Component* c : compArray) {
		if (c) c->update();
	}
}

void Entity::render() {
	for (auto& c : compArray) {
		c->render();
	}
}