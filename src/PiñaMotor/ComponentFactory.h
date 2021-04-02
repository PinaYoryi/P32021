#pragma once
#include <string>
#include <unordered_map>
#include "ecs.h"
//TODO Decidir si dejar la macro o no
//macro que igual no hace falta, mirar si la necesitamos o no
#ifdef BUILD_DLL
#define DLL_INTERFACE __declspec(dllexport)
#else
#define DLL_INTERFACE __declspec(dllimport)
#endif

class Component;

typedef Component* (*componentInstanceGenerator) ();

class ComponentFactory {
public:
	///<summary>
	///devuelve una instancia del singleton 
	///</summary>
	DLL_INTERFACE static ComponentFactory& getInstance();
	
	///<summary>
	///Devuele el componente que quieres si esta guardado en mGenerators, si no existe devuelve nullptr
	///</summary>
	DLL_INTERFACE Component* getComponent(size_t typeName);
	
	///<summary>
	///Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	///</summary>
	DLL_INTERFACE bool registerGenerator(size_t typeName, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};
	///<summary>
	//tabla hash donde guardamos todos los componentes, size_t es el nombre del ecs
	//componentInstanceGenerator es el componente como tal
	///</summary>
	std::unordered_map<size_t, componentInstanceGenerator> _mGenerators;
};