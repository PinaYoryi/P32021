#pragma once

#include <SDL.h>
#undef main
#include "Vector3.h"

#ifdef _DEBUG
#include <iostream>
#endif

//N�mero de botones que tiene un rat�n.
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
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static Input* getInstance();

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
	/// Devuelve si se ha movido el rat�n.
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
	/// Devuelve 1 si se gira la rueda del raton hacia arriba, -1 hacia abajo y 0 si no se est� moviendo.
	/// </summary>
	int wheelDir();

	/// <summary>
	/// Devuelve la posici�n del rat�n.
	/// </summary>
	Vector3 getMousePos(); //Todo: Actualizar a vector2

protected:
	static Input* _singleton;
	
	//Estructuras con la informaci�n de los teclados del frame actual y del anterior y su numero de teclas.
	const Uint8* _currKeyboard;
	Uint8* _prevKeyboard;
	int _numKeys;

	//Estructuras con la informaci�n del rat�n.
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