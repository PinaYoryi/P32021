#pragma once
#include "Component.h"


class SkyBox : public Component
{
public:
	SkyBox();
	~SkyBox();
	bool init(const std::map<std::string, std::string>& mapa) override;

};

