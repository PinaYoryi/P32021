#pragma once
#include <string>
#include <unordered_map>
#include "ecs.h"


class Component;

typedef Component* (*componentInstanceGenerator) ();

class ComponentFactory {
public:
	///<summary>
	///devuelve una instancia del singleton 
	///</summary>
	 static ComponentFactory& getInstance();
	
	///<summary>
	///Devuele el componente que quieres si esta guardado en mGenerators, si no existe devuelve nullptr
	///</summary>
	template<typename T>
	 T* getComponent() {
		 auto it = _mGenerators.find(indexOf<T, ComponentsList>);
		 if (it != _mGenerators.end())
		 {
			 return it->second();
		 }
		 return nullptr;
	 }
	
	///<summary>
	///Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	///</summary>
	template<typename T>
	 bool registerGenerator(const componentInstanceGenerator& instGenerator) {
		 return _mGenerators.insert(std::make_pair(indexOf<T, ComponentsList>, instGenerator)).second;
	 }

private:
	ComponentFactory() {};
	~ComponentFactory() {};
	///<summary>
	//tabla hash donde guardamos todos los componentes, size_t es el nombre del ecs
	//componentInstanceGenerator es el componente como tal
	///</summary>
	std::unordered_map<size_t, componentInstanceGenerator> _mGenerators;
};