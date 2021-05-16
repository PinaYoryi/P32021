#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

const std::string DEFAULT_NAME = "";
const std::string DEFAULT_TEXT = "";
const glm::vec2 DEFAULT_POSITION = glm::vec2(0.0f, 0.0f);
const glm::vec2 DEFAULT_SIZE = glm::vec2(0.0f, 0.0f);

/// <summary>
/// espacio de nombres para hacer llamada al puntero del atributo de la clase GUI
/// </summary>
namespace CEGUI {
    class Window;
}

class ButtonComponent: public Component {

public:

	ButtonComponent() {};

	~ButtonComponent();

	/// <summary>
	///	inicializa un botón default en caso de fallo 
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;
	/// <summary>
	/// método para crear el botón
	/// </summary>
	CEGUI::Window* create(const std::string& text, const glm::vec2 position, const glm::vec2 size, const std::string& name);
	/// <summary>
	/// método abstracto para gestionar el input del button
	/// </summary>
	virtual void onClick() = 0;

protected:
	//atributo propio de la clase
    CEGUI::Window* _windowC;
};

