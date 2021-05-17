#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

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
	///	Inicializa un botón default en caso de fallo 
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;
	/// <summary>
	/// Método abstracto para gestionar el input del button
	/// </summary>
	virtual void onClick() {};

protected:
	/// <summary>
	/// Método para crear el botón
	/// </summary>
	CEGUI::Window* create(const std::string& text, const glm::vec2 position, const glm::vec2 size, const std::string& name);

	//atributo propio de la clase
    CEGUI::Window* _windowC;
	glm::vec2 _position;
	glm::vec2 _size;
	std::string _name;
	std::string _text;
};