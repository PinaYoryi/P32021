#include "Entity.h"
#include "ComponentFactory.h"
#include <map>


Entity::Entity() : _name("Entity")
{
	
	addComponent<Transform>(std::map<std::string,std::string>());
	//_compArray[indexOf<Transform, ComponentsList>] = ComponentFactory::getInstance().getComponent<Transform>();
}

Entity::Entity(char* entityName) : _name(entityName)
{
	//_compArray[indexOf<Transform, ComponentsList>] = ComponentFactory::getInstance().getComponent<Transform>();
}

Entity::~Entity() {

}

////template<typename T, typename ...TArgs>
//T* Entity::addComponent()
//{
//
//	T* t=(ComponentFactory::getInstance().getComponent<T>());
//	_compArray[indexOf<T, ComponentsList>] = t;
//	t->init(args...);
//	return t;
//}

//template<typename T>
//T* Entity::getComponent()
//{
//	return _compArray[indexOf<T, ComponentsList>];
//}

//template<typename T>
//bool Entity::hasComponent() 
//{
//	return _compArray[indexOf<T, ComponentsList>];
//}

//template<typename T>
//void Entity::removeComponent() 
//{
//	//¿Quitar de unique pointers?
//	delete _compArray[indexOf<T, ComponentsList>];
//	_compArray[indexOf<T, ComponentsList>] = nullptr;
//}

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