#pragma once
#include <string>
#include <unordered_map>

#ifdef BUILD_DLL
#define DLL_INTERFACE __declspec(dllexport)
#else
#define DLL_INTERFACE __declspec(dllimport)
#endif

class Component;

typedef Component* (*componentInstanceGenerator) ();

class ComponentFactory {
public:
	DLL_INTERFACE bool registerGenerator(const char* typeName, const componentInstanceGenerator& instGenerator);

private:
	ComponentFactory() {};
	~ComponentFactory() {};

	std::unordered_map<std::string, componentInstanceGenerator> mGenerators;
};