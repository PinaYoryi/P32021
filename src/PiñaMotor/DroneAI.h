#pragma once
#include "Component.h"
#include "Entity.h"

class DroneAI : public Component {
public:
	DroneAI():_objective(nullptr), _strength(10){};
	bool init(const std::map<std::string, std::string>& mapa) override;
	void update() override;
	void onCollisionStart(Entity* other) override;
protected:
private:
	Entity* _objective;
	float _strength;
};