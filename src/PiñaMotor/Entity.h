#pragma once
#include "ecs.h"
#include <vector>
#include <string>
#include <vector>
#include <memory>

class Component{};
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
	T* getComponent(ecs::CmpIdType id);

	bool hasComponent(ecs::CmpIdType id);

	template<typename T>
	void removeComponent(ecs::CmpIdType id);

	void update();

	void render();
};