#pragma once
#include <string>
#include <unordered_map>

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
	Component* getComponent(size_t index);

	///<summary>
	///Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	///</summary>
	bool registerGenerator(size_t index, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};
	///<summary>
	//tabla hash donde guardamos todos los componentes, size_t es el nombre del ecs
	//componentInstanceGenerator es el componente como tal
	///</summary>
	std::unordered_map<size_t, componentInstanceGenerator> _mGenerators;
};