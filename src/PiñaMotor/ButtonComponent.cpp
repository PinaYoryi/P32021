#include "ButtonComponent.h"
#include "Entity.h"
#include "Gui.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>

bool ButtonComponent::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("text") == mapa.end() || mapa.find("position") == mapa.end() ||
		mapa.find("size") == mapa.end() || mapa.find("name") == mapa.end()) return false;

	std::string t = mapa.at("text");

	std::string p = mapa.at("position");
	std::string::size_type pa = 0, pb = 0;
	float a = std::stof(p, &pa);
	float b = std::stof(p.substr(pa + 1), &pb);

	std::string s = mapa.at("size");
	std::string::size_type sa = 0, sb = 0;
	float x = std::stof(s, &sa);
	float y = std::stof(s.substr(sa + 1), &sb);

	std::string n = mapa.at("name");

	create(t, glm::vec2(a, b), glm::vec2(x, y), n);

	return true;
}

ButtonComponent::~ButtonComponent() {
	_windowC = nullptr;
}

CEGUI::Window* ButtonComponent::create(const std::string& text, const glm::vec2 position, const glm::vec2 size, const std::string& name) {
	_windowC = Gui::GetInstance()->createButton(text, position, size, name);
	return _windowC;
}