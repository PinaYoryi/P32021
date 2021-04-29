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
	///Devuele el componente que quieres si esta guardado en mGenerators, si no existe devuelve nullptr
	///</summary>
	Component* getComponent(std::string name);

	/// <summary>
	/// Devuelve el indice asociado al componente con el nombre name
	/// </summary>
	size_t getComponentIndex(std::string name);

	///<summary>
	///Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	///</summary>
	bool registerGenerator(size_t index, std::string compName, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};
	///<summary>
	//tabla hash donde guardamos todos los componentes, size_t es el nombre del ecs
	//componentInstanceGenerator es el componente como tal
	///</summary>
	std::unordered_map<size_t, componentInstanceGenerator> _mGenerators;
	std::unordered_map<std::string, size_t> _mCompNames;
};