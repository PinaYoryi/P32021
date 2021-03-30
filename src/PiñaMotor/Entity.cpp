#include "Entity.h"

Entity::Entity() : name("Entity")
{
	compArray[/*Lista<Transform>*/] = ComponentFactory::getInstance().getComponent(/*Lista<Transform>*/);
}

Entity::Entity(char* entityName) : name(entityName)
{
	compArray[/*Lista<Transform>*/] = ComponentFactory::getInstance().getComponent(/*Lista<Transform>*/);
}

Entity::~Entity() {

}

template<typename T, typename ...TArgs>
T* Entity::addComponent(TArgs ...args)
{
	T* t(ComponentFactory::getInstance().getComponent(/*Lista<T>*/));
	componentsArray_[/*Lista<T>*/] = t;
	t->init();
	return t;
}

template<typename T>
T* Entity::getComponent()
{
	return compArray[/*Lista<T>*/];
}

template<typename T>
bool Entity::hasComponent() 
{
	return compArray[/*Lista<T>*/];
}

template<typename T>
void Entity::removeComponent() 
{
	//¿Quitar de unique pointers?
	delete compArray[/*Lista<T>*/];
	compArray[id] = nullptr;
}

void Entity::update() {
	for (Component* c : compArray) {
		if (c) c->Update();
	}
}

void Entity::render() {
	/*for (auto& c : compArray) {
		if(c) c->Render();
	}*/
}