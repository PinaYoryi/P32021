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
	// Tipos de botones, sirven para gestionar la accion del boton al hacerle click
	enum class ButtonType {
		CHANGE_SCENE = 0,
		RESUME = 1,
		EXIT = 2
	};
	ButtonComponent(): _button(nullptr) {};
	~ButtonComponent();

	/// <summary>
	///	Inicializa el boton leyendo el archivo de lua
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Método abstracto para gestionar el input del button
	/// </summary>
	virtual void onClick();

	/// <summary>
	/// Fija un nuevo valor para el texto
	/// </summary>
	void setText(std::string text);

protected:
	// Atributos propios de la clase
	// Es importante tener en cuenta que la posicion y la escala van de 0 a 1,
	// siendo el (0, 0) la posicion de la esquina superior izquierda
    CEGUI::Window* _button;
	ButtonType _buttonType = ButtonType::CHANGE_SCENE;
	glm::vec2 _position = glm::vec2(0.0, 0.0);
	glm::vec2 _size = glm::vec2(0.0, 0.0);
	std::string _name = "";
	std::string _text = "";
	std::string _nextScene = "myscript.lua";
	bool _continueBullet = false;//si es true, al ser pulsado el boton se continua las fisicas

};