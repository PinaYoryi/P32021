#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

namespace CEGUI {
	class Window;
}

class ImageComponent: public Component
{
public:
	ImageComponent();
	~ImageComponent();

	bool init(const std::map<std::string, std::string>& mapa) override;

private:
	CEGUI::Window* _image;
	glm::vec2 _position = glm::vec2(0.0, 0.0);
	glm::vec2 _size = glm::vec2(0.0, 0.0);
	std::string _name = "";
	std::string _text = "";
};
