#pragma once
#include <map>
#include <string>
//TODO : hacer friend con entity
//clase abstracta de todos los componentes
class Component {
public:
	virtual bool init(const std::map<std::string, std::string>& mapa) = 0;

	virtual void Start() {} ;

	virtual bool OnTriggerStart() {};
	virtual bool OnTriggerStay() {};
	virtual bool OnTriggerEnd() {};

	virtual bool OnCollisionStart() {};
	virtual bool OnCollisionStay() {};
	virtual bool OnCollisionEnd() {};

	virtual void Update() {};
	virtual void FixedUpdate(){};

	void SetActive(bool toggle) 
	{
		active = toggle;
	}
protected:
	virtual void Render() {};
	bool active;
};