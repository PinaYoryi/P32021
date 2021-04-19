#pragma once

#include <SDL.h>
#undef main
#include "Vector2.h"

#ifdef _DEBUG
#include <iostream>
#endif

//Número de botones que tiene un ratón.
const int NUM_MOUSE_BUTTONS = 3;

enum SDL_Mousecode {
	SDL_MOUSECODE_LEFT,
	SDL_MOUSECODE_MIDDLE,
	SDL_MOUSECODE_RIGHT
};

class Input {
public:
	~Input() {
		delete _prevKeyboard;
	}

	/// <summary>
	/// Devuelve una instancia de la clase. Devuelve nullptr por defecto si no se ha inicializado.
	/// Para inicializarla se usa Init().
	/// </summary>
	static Input* GetInstance();

	/// <summary>
	/// Inicializa la clase Input con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya había sido inicializada.
	/// Todo: Implementar los parametros a inicializar.
	/// </summary>
	static bool Init();

	/// <summary>
	/// Actualiza las estructuras de teclados con los nuevos inputs.
	/// </summary>
	void update();

	/// <summary>
	/// Devuelve true si se ha pulsado por primera vez una tecla de teclado, false en otro caso.
	/// </summary>
	bool keyDown(SDL_Scancode key);

	/// <summary>
	/// Devuelve true si una tecla de teclado se estaba pulsando y se ha dejado de pulsar, false en otro caso.
	/// </summary>
	bool keyUp(SDL_Scancode key);

	/// <summary>
	/// Devuelve true si una tecla de teclado se estaba pulsando y se sigue pulsando, false en otro caso.
	/// </summary>
	bool keyHold(SDL_Scancode key);

	/// <summary>
	/// Devuelve si se ha movido el ratón.
	/// </summary>
	bool mouseMovement();

	/// <summary>
	/// Devuelve true si se ha pulsado por primera vez una tecla de raton, false en otro caso.
	/// </summary>
	bool mouseDown(SDL_Mousecode button);

	/// <summary>
	/// Devuelve true si una tecla de raton se estaba pulsando y se ha dejado de pulsar, false en otro caso.
	/// </summary>
	bool mouseUp(SDL_Mousecode button);

	/// <summary>
	/// Devuelve true si una tecla de raton se estaba pulsando y se sigue pulsando, false en otro caso.
	/// </summary>
	bool mouseHold(SDL_Mousecode button);
	
	/// <summary>
	/// Devuelve 1 si se gira la rueda del raton hacia arriba, -1 hacia abajo y 0 si no se está moviendo.
	/// </summary>
	int wheelDir();

	/// <summary>
	/// Devuelve la posición del ratón.
	/// </summary>
	Vector2<int> getMousePos(); //Todo: Actualizar a vector2

protected:
	static Input* _singleton;
	
	//Estructuras con la información de los teclados del frame actual y del anterior y su numero de teclas.
	const Uint8* _currKeyboard;
	Uint8* _prevKeyboard;
	int _numKeys;

	//Estructuras con la información del ratón.
	//El primer elemento de los vectores representa el valor actual y el segundo el del frame anterior.
	bool _mouseMotion;
	bool _prevMouse[NUM_MOUSE_BUTTONS];
	bool _currMouse[NUM_MOUSE_BUTTONS];
	int _wheel; //1 hacia arriba, 0 sin movimiento, -1 hacia abajo.

	Input();

	/// <summary>
	/// Actualiza las estructuras de datos del frame anterior antes de modificar las del frame actual
	/// </summary>
	void makeDataCopy();
};