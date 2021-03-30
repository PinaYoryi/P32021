#pragma once
#include "ecs.h"
#include "Component.h"

class Transform : public Component {};

using namespace std;

class Entity {
private:
	const char* name;
	//std::vector<unique_ptr<Component>> compUnique;
	Component* compArray[ecs::_LastCmptId_];
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