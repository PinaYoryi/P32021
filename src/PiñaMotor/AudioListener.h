#pragma once
#include "Component.h"
#include <fmod.hpp>
#include "Vector3.h"
#include "Audio.h"

class AudioListener : public Component {


public:
	AudioListener() {};
	AudioListener(Vector3<float> position, Vector3<float> velocity);
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void setPosition(Vector3<float> position) { _position.x = position.getX(); _position.y = position.getY(); _position.z = position.getZ();};
	Vector3<float> getPosition() { return Vector3<float>(_position.x,_position.y,_position.z); };

	void setVelocity(Vector3<float> velocity) { _velocity.x = velocity.getX(); _velocity.y = velocity.getY(); _velocity.z = velocity.getZ(); };
	Vector3<float> getPosition() { return Vector3<float>(_velocity.x, _velocity.y, _velocity.z); };

	void update();


private:

	FMOD::System* _system;
	FMOD_VECTOR _position;
	FMOD_VECTOR _velocity;
	FMOD_VECTOR _forward;
	FMOD_VECTOR _up;
};