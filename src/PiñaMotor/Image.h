#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

// Espacio de nombres para hacer llamada al puntero del atributo de la clase GUI
namespace CEGUI {
    class Window;
}

class Image: public Component {
public:
	// Tipos de botones, sirven para gestionar la accion del boton al hacerle click
	// Tipos de botones, sirven para gestionar la accion del boton al hacerle click
	
	Image(): _button(nullptr) {};
	~Image();

	/// <summary>
	///	Inicializa el boton leyendo el archivo de lua
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;



protected:
	// Atributos propios de la clase
	// Es importante tener en cuenta que la posicion y la escala van de 0 a 1,
	// siendo el (0, 0) la posicion de la esquina superior izquierda
    CEGUI::Window* _button;
	glm::vec2 _position = glm::vec2(0.0, 0.0);
	glm::vec2 _size = glm::vec2(0.0, 0.0);
	std::string _name = "";
	std::string _text = "";
	std::string _nextScene = "myscript.lua";
};