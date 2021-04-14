#pragma once
#include "Component.h"

class AudioListener : public Component {
public:
	AudioListener() {};
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}
};