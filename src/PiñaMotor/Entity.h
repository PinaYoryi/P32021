#pragma once
#include "Component.h"
#include "ecs.h"
#include "ComponentFactory.h"
#include <map>
using namespace std;

class Entity {
public:
	Entity();
	Entity(char* entityName, int id);

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

	Component* addComponent(const std::string& compName, const std::map<std::string, std::string>& map) { // TODO: Mirar si esto esta bien hecho
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
		return static_cast<T*>(_compArray[indexOf<T, ComponentsList>]);
	}

	template<typename T>
	bool hasComponent() {
		return _compArray[indexOf<T, ComponentsList>];
	}

	template<typename T>
	bool removeComponent() {
		//¿Quitar de unique pointers?	
		bool deleted = hasComponent<T>();
		if (deleted) {
			//eliminar el componente que queremos
			for (int i = 0; i < compUnique.size(); ++i) {
				if (dynamic_cast<T*>(compUnique[i].get())) {
					*compUnique[i] = *compUnique.back();
					compUnique.pop_back();
					break;
				}
			}		
			_compArray[indexOf<T, ComponentsList>] = nullptr;
		}
		return deleted;
	}

	const char* getName() { return _name; }

	void update();

	void fixedUpdate();

	void render();

private:
	const char* _name;

	int _id;
	//aqui estaran los componentes de esta entidad
	std::vector<unique_ptr<Component>> compUnique;
	//aqui estaran todos los posibles punteros a componentes existentes
	Component* _compArray[numOfComponents];
};