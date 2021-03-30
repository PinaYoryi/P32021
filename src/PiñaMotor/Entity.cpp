#include "Entity.h"

Entity::Entity() : _name("Entity")
{
	_compArray[indexOf<Transform, ComponentsList>] = ComponentFactory::getInstance().getComponent(indexOf<Transform, ComponentsList>);
}

Entity::Entity(char* entityName) : _name(entityName)
{
	_compArray[indexOf<Transform, ComponentsList>] = ComponentFactory::getInstance().getComponent(indexOf<Transform, ComponentsList>);
}

Entity::~Entity() {

}

template<typename T, typename ...TArgs>
T* Entity::addComponent(TArgs ...args)
{
	T* t(ComponentFactory::getInstance().getComponent(indexOf<T, ComponentsList>));
	_compArray[indexOf<T, ComponentsList>] = t;
	t->init();
	return t;
}

template<typename T>
T* Entity::getComponent()
{
	return _compArray[indexOf<T, ComponentsList>];
}

template<typename T>
bool Entity::hasComponent() 
{
	return _compArray[indexOf<T, ComponentsList>];
}

template<typename T>
void Entity::removeComponent() 
{
	//¿Quitar de unique pointers?
	delete _compArray[indexOf<T, ComponentsList>];
	_compArray[indexOf<T, ComponentsList>] = nullptr;
}

void Entity::update() {
	for (Component* c : _compArray) {
		if (c) c->Update();
	}
}

void Entity::render() {
	/*for (auto& c : compArray) {
		if(c) c->Render();
	}*/
}