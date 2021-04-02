#pragma once
#include "Component.h"

class Transform : public Component {
public:
	Transform() {

	}

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}
};