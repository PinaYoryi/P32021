#include "ImageComponent.h"
#include "Entity.h"
#include "Gui.h"
#include "MotorLoop.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include "ResourceManager.h"

ImageComponent::ImageComponent() : _image(nullptr)
{
}

ImageComponent::~ImageComponent()
{
	CEGUI::WindowManager::getSingleton().destroyWindow(_image);
	setActive(false);
}

bool ImageComponent::init(const std::map<std::string, std::string>& mapa)
{
	if (mapa.find("source") == mapa.end() || mapa.find("position") == mapa.end() ||
		mapa.find("size") == mapa.end() || mapa.find("name") == mapa.end() || 
		mapa.find("properties") == mapa.end()) return false;

	std::string o = mapa.at("source");

	std::string p = mapa.at("position");
	std::string::size_type pa = 0, pb = 0;
	float a = std::stof(p, &pa);
	float b = std::stof(p.substr(pa + 1), &pb);

	std::string s = mapa.at("size");
	std::string::size_type sa = 0, sb = 0;
	float x = std::stof(s, &sa);
	float y = std::stof(s.substr(sa + 1), &sb);

	std::string n = mapa.at("name");

	std::string an = mapa.at("properties");
	std::vector<std::string> proper;
	int iterator = 0;
	std::string na = "";
	while ((na = an.substr(0, an.find(","))) != "") {
		iterator = na.length() + 1;
		if (iterator != an.length() + 1)
		{
			an = an.substr(iterator);
			proper.push_back(na);
		}
		else {
			proper.push_back(na);
			break;
		}
	};

	_image = Gui::GetInstance()->createImage(o, glm::vec2(a, b), glm::vec2(x, y), n, proper);
	
	return true;
}
