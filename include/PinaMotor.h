#pragma once
#include <string>

class PinaMotor {
public:
	PinaMotor() {};
	~PinaMotor() {};

	/// <summary>
	/// Inicia el motor. Arranca los motores de renderizado, físicas y sonido.
	/// </summary>
	bool init(std::string windowName);

	/// <summary>
	/// Carga la escena inicial del juego a partir del archivo dado y cede el control al loop principal.
	/// </summary>
	bool launch(std::string sceneName);

	/// <summary>
	/// Cierra los recursos creados por la clase.
	/// </summary>
	void close();
};