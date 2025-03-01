#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

namespace CEGUI {
	class Window;
}

class TextComponent: public Component
{
public:
	TextComponent();
	~TextComponent();

	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Fija un nuevo valor para el texto
	/// </summary>
	void setText(std::string text);

private:
	CEGUI::Window* _textG;
	glm::vec2 _position = glm::vec2(0.0, 0.0);
	glm::vec2 _size = glm::vec2(0.0, 0.0);
	std::string _name = "";
	std::string _text = "";
};
