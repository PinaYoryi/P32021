#pragma once
#include "Component.h"
#include <fmod.hpp>
#include "Vector3.h"
#include "Audio.h"

class AudioListener : public Component {
public:
	AudioListener();
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void set3DAtributes(Vector3<float> position, Vector3<float> velocity);

	void setPosition(Vector3<float> position) { _position.x = position.x; _position.y = position.y; _position.z = position.z;};
	Vector3<float> getPosition() { return Vector3<float>(_position.x,_position.y,_position.z); };

	void setVelocity(Vector3<float> velocity) { _velocity.x = velocity.x; _velocity.y = velocity.y; _velocity.z = velocity.z; };
	Vector3<float> getVelocity() { return Vector3<float>(_velocity.x, _velocity.y, _velocity.z); };

	void setUp(Vector3<float> up) { _up.x = up.x; _up.y = up.y; _up.z = up.z; };
	Vector3<float> getUp() { return Vector3<float>(_up.x, _up.y, _up.z); };

	void setForward(Vector3<float> forward) { _forward.x = forward.x; _forward.y = forward.y; _forward.z = forward.z; };
	Vector3<float> getForward() { return Vector3<float>(_forward.x, _forward.y, _forward.z); };

	virtual void update() override;

private:
	void errorCheck(FMOD_RESULT result);

	FMOD_RESULT _result;
	FMOD_VECTOR v;
	FMOD_VECTOR p;
	FMOD_VECTOR f;
	FMOD_VECTOR u;
	FMOD::System* _system;
	Vector3<float> _position;
	Vector3<float> _velocity;
	Vector3<float> _forward;
	Vector3<float> _up;
};