#pragma once
#include "Component.h"
#include <fmod.hpp>
#include "Vector3.h"
#include "Audio.h"

class AudioListener : public Component {
public:
	AudioListener(Vector3<float> position = { 0.0f, 0.0f, 0.0f }, Vector3<float> velocity = { 0.0f, 0.0f, 0.0f });
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void setPosition(Vector3<float> position) { _position.x = position.x; _position.y = position.y; _position.z = position.z;};
	Vector3<float> getPosition() { return Vector3<float>(_position.x,_position.y,_position.z); };

	void setVelocity(Vector3<float> velocity) { _velocity.x = velocity.x; _velocity.y = velocity.y; _velocity.z = velocity.z; };
	Vector3<float> getVelocity() { return Vector3<float>(_velocity.x, _velocity.y, _velocity.z); };

	void update() override;

private:
	Audio* _instance;
	FMOD::System* _system;
	FMOD_VECTOR _position;
	FMOD_VECTOR _velocity;
	FMOD_VECTOR _forward;
	FMOD_VECTOR _up;
};