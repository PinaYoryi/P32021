#pragma once
#include "Component.h"
#include "Entity.h"

class DroneAI : public Component {
public:
	DroneAI() {};
	bool init(const std::map<std::string, std::string>& mapa) override;
	void update() override;
protected:
private:
	Entity* _objective;
	float _strength;
};