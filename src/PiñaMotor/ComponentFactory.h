#pragma once
#include <string>
#include <unordered_map>

//macro
#ifdef BUILD_DLL
#define DLL_INTERFACE __declspec(dllexport)
#else
#define DLL_INTERFACE __declspec(dllimport)
#endif

class Component;

typedef Component* (*componentInstanceGenerator) ();

class ComponentFactory {
public:
	//devuelve una instancia del singleton 
	DLL_INTERFACE static ComponentFactory& get();
	//Devuele el componente que quieres si esta guardado en mGenerators, si no existe devuelve nullptr
	DLL_INTERFACE Component* getComponent(const char* typeName);
	//Registra el nuevo componente que le pasas, primero el nombre (identificador) y luego el componente como tal
	DLL_INTERFACE bool registerGenerator(const char* typeName, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};

	std::unordered_map<std::string, componentInstanceGenerator> mGenerators;
};