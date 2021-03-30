#pragma once
#include "Component.h"
#include "ecs.h"

class Transform : public Component {};

using namespace std;

class Entity {
private:
	const char* _name;
	//std::vector<unique_ptr<Component>> compUnique;
	Component* _compArray[numOfComponents];
public:
	Entity();
	Entity(char* entityName);

	~Entity();

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs ...args);

	template<typename T>
	T* getComponent();

	template<typename T>
	bool hasComponent();

	template<typename T>
	void removeComponent();

	void update();

	void render();
};