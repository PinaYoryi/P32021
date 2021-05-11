#pragma once
#include "Component.h"
#include "ecs.h"
#include "ComponentFactory.h"
#include <map>
using namespace std;

class Entity {
public:
	Entity();
	Entity(std::string entityName, int id);

	~Entity();

	template<typename T>
	Component* addComponent(const std::map<std::string, std::string>& map) {
		Component* t = ComponentFactory::getInstance().getComponent(indexOf<T, ComponentsList>);
		t->_myEntity = this;//ponemos la entidad en el componente
		std::unique_ptr<Component> upt (t);
		compUnique.push_back(std::move(upt));
		_compArray[indexOf<T, ComponentsList>] = t;
		
		if (t->init(map)) {
			return t;
		}
		throw "Error de carga de componente con el indice " + indexOf<T, ComponentsList>; // TODO: Hacer un sistema de excepciones
	}

	Component* addComponent(const std::string& compName, const std::map<std::string, std::string>& map) {
		Component* t = ComponentFactory::getInstance().getComponent(compName);
		t->_myEntity = this;//ponemos la entidad en el componente
		std::unique_ptr<Component> upt(t);
		compUnique.push_back(std::move(upt));
		_compArray[ComponentFactory::getInstance().getComponentIndex(compName)] = t;

		if (t->init(map)) {
			return t;
		}
		throw "Error de carga de componente con el indice " + ComponentFactory::getInstance().getComponentIndex(compName); // TODO: Hacer un sistema de excepciones
	}

	template<typename T>
	T* getComponent() {
		try {
			return static_cast<T*>(_compArray[indexOf<T, ComponentsList>]);
		}
		catch (...) { throw "Could not find component: " + indexOf<T, ComponentsList>; }
	}

	template<typename T>
	bool hasComponent() {
		return _compArray[indexOf<T, ComponentsList>];
	}

	const std::string getName() { return _name; }

	void update();

	void fixedUpdate();

	void render();

	std::vector<unique_ptr<Component>>* getComponents() { return &compUnique; }
	
private:
	std::string _name;

	int _id;
	//aqui estaran los componentes de esta entidad
	std::vector<unique_ptr<Component>> compUnique;
	//aqui estaran todos los posibles punteros a componentes existentes
	Component* _compArray[numOfComponents];
};