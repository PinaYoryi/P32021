#pragma once
#include "Component.h"
#include <fmod.hpp>
#include "Vector3.h"

class AudioListener : public Component {


public:
	AudioListener() {};
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void setPosition() {};
	Vector3<float> getPosition() { return _position; };

private:

	Vector3<float> _position;
};