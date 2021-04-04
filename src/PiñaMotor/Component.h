#pragma once
#include <map>
#include <string>
//#include "OgreSceneNode.h"
//#include "OgreEntity.h"
//clase abstracta de todos los componentes
class Entity;
class Component {
	friend  Entity;

public:
	virtual bool init(const std::map<std::string, std::string>& mapa) = 0;

	virtual void Start() {} ;

	virtual void OnTriggerStart() {};
	virtual void OnTriggerStay() {};
	virtual void OnTriggerEnd() {};

	virtual void OnCollisionStart() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionEnd() {};

	virtual void Update() {};
	virtual void FixedUpdate(){};

	void SetActive(bool toggle) 
	{
		_active = toggle;
	}
	//TODO:Como cambiar cosas de un componente a otro, pasando por la entidad
	/*template<typename T>
	T* getComponent() {
		return _myEntity->getComponent<T>();
	}*/

protected:
	virtual void Render() {};
	bool _active;
	Entity* _myEntity;
	//Ogre::SceneNode* _ogreNode;//nodo de ogre 
	//Ogre::Entity* _ogreEntity;//entidad de ogre
};