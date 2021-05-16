#include "ButtonComponent.h"
#include "Entity.h"
#include "Gui.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>

//sssssssssssssssssssss
bool ButtonComponent::init(const std::map<std::string, std::string>& mapa) {
	//if (mapa.find("position") == mapa.end() || mapa.find("rotation") == mapa.end() || mapa.find("scale") == mapa.end()) return false;
	//std::string::size_type sz = 0, sa = 0;

	//std::string s = mapa.at("position");
	//float a = std::stof(s, &sz);
	//string temp = s.substr(sz + 1);
	//float b = std::stof(temp, &sa);
	//float c = std::stof(s.substr(sz + sa + 2));
	//DEFAULT_POSITION = { std::stof(s, &sz), std::stof(s.substr(sz + 1), &sa), std::stof(s.substr(sz + sa + 2)) };

	return true;
}

