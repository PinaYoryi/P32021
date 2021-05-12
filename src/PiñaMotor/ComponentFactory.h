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
	Component* getComponent(std::string name);

	///<summary>
	///Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	///</summary>
	bool registerGenerator(std::string compName, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};
	///<summary>
	// Tabla hash donde guardamos todos los componentes, string es el nombre
	// componentInstanceGenerator es el componente como tal
	///</summary>
	std::unordered_map<std::string, componentInstanceGenerator> _mGenerators;
};