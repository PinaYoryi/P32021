#pragma once
#include <map>
#include <string>
class Entity;

//clase abstracta de todos los componentes
class Component {
	friend  Entity;

public:
	virtual bool init(const std::map<std::string, std::string>& mapa) = 0;

	virtual void start() {};

	virtual void onTriggerStart(Entity* other) {};
	virtual void onTriggerStay(Entity* other) {};
	virtual void onTriggerEnd(Entity* other) {};

	virtual void onCollisionStart(Entity* other) {};
	virtual void onCollisionStay(Entity* other) {};
	virtual void onCollisionEnd(Entity* other) {};

	virtual void update() {};
	virtual void fixedUpdate() {};
	virtual ~Component() {};
	void setActive(bool toggle) 
	{
		_active = toggle;
	}

	Entity* getEntity() { return _myEntity; }
	//TODO:Como cambiar cosas de un componente a otro, pasando por la entidad
	/*template<typename T>
	T* getComponent() {
		return _myEntity->getComponent<T>();
	}*/

protected:
	virtual void render() {};
	bool _active = true;
	Entity* _myEntity = nullptr;
};