#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

// Espacio de nombres para hacer llamada al puntero del atributo de la clase GUI
namespace CEGUI {
    class Window;
}

class ButtonComponent: public Component {
public:
	// Tipos de botones, sirven para gestionar la accion del boton al hacerle click
	enum ButtonType {
		CHANGE_SCENE = 0,
		EXIT = 1
	};

	ButtonComponent() {};
	~ButtonComponent();

	/// <summary>
	///	Inicializa el boton leyendo el archivo de lua
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Método abstracto para gestionar el input del button
	/// </summary>
	virtual void onClick();

protected:
	// Atributos propios de la clase
    CEGUI::Window* _button;
	ButtonType _buttonType = ButtonType::CHANGE_SCENE;
	glm::vec2 _position = glm::vec2(0.0, 0.0);
	glm::vec2 _size = glm::vec2(0.0, 0.0);
	std::string _name = "";
	std::string _text = "";
	std::string _nextScene = "myscript.lua";
};