#pragma once
#include "Component.h"
#include "ecs.h"
using namespace std;
class Entity {
private:
	const char* _name;
	//std::vector<unique_ptr<Component>> compUnique;
	Component* _compArray[numOfComponents];
public:
	Entity();
	Entity(char* entityName);

	~Entity();

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs ...args) {
		T* t = (ComponentFactory::getInstance().getComponent<T>());
		_compArray[indexOf<T, ComponentsList>] = t;
		t->init(args...);
		return t;
	}

	template<typename T>
	T* getComponent() {
		return _compArray[indexOf<T, ComponentsList>];
	}

	template<typename T>
	bool hasComponent() {
		return _compArray[indexOf<T, ComponentsList>];
	}

	template<typename T>
	void removeComponent() {
		//¿Quitar de unique pointers?
		delete _compArray[indexOf<T, ComponentsList>];
		_compArray[indexOf<T, ComponentsList>] = nullptr;
	}

	void update();

	void render();
};