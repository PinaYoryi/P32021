#pragma once
#include "Component.h"
#include "ecs.h"
#include "ComponentFactory.h"
using namespace std;

class Entity {
public:
	Entity();
	Entity(char* entityName);

	~Entity();

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs &&...args) {
		Component* t = ComponentFactory::getInstance().getComponent(indexOf<T, ComponentsList>);
		t->_myEntity = this;//ponemos la entidad en el componente
		std::unique_ptr<Component> upt (t);
		compUnique.push_back(std::move(upt));
		_compArray[indexOf<T, ComponentsList>] = t;
		std::map<std::string, std::string> map;
		
		// TODO: Que se cargue el diccionario con los args
		if (t->init(map)) {
			return static_cast<T*>(t);
		}
		cout << "Error carga componente\n";
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

	void render();

private:
	const char* _name;
	//aqui estaran los componentes de esta entidad
	std::vector<unique_ptr<Component>> compUnique;
	//aqui estaran todos los posibles punteros a componentes existentes
	Component* _compArray[numOfComponents];
};