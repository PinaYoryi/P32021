#pragma once
#include "Component.h"
#include "ecs.h"
#include "ComponentFactory.h"
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
	Component* addComponent(TArgs ...args) {
		Component* t = ComponentFactory::getInstance().getComponent(indexOf<T, ComponentsList>);
		_compArray[indexOf<T, ComponentsList>] = t;
		std::map<std::string, std::string> map;
		// TODO: Que se cargue el diccionario con los args
		if (t->init(map)) {
			return t;
		}
		cout << "Error carga componente\n";
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