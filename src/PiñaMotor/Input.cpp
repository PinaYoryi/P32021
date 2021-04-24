#include "Input.h"
#include "MotorLoop.h"

Input* Input::_singleton = nullptr;

Input* Input::GetInstance() {
	return _singleton;
}

bool Input::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new Input(); return true;
}


Input::Input() : 
	_mouseMotion(false),
	_wheel(0),
	_currKeyboard(SDL_GetKeyboardState(&_numKeys)),
	_prevKeyboard(new Uint8[_numKeys]) {
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++) {
		_prevMouse[i] = false; _currMouse[i] = false;
	}
};

void Input::update() {
	makeDataCopy();
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			MotorLoop::GetInstance()->stopLoop();
			break;
		case SDL_MOUSEMOTION:
			_mouseMotion = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) _currMouse[SDL_MOUSECODE_LEFT] = true;
			else if (event.button.button == SDL_BUTTON_MIDDLE) _currMouse[SDL_MOUSECODE_MIDDLE] = true;
			else if (event.button.button == SDL_BUTTON_RIGHT) _currMouse[SDL_MOUSECODE_RIGHT] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) _currMouse[SDL_MOUSECODE_LEFT] = false;
			else if (event.button.button == SDL_BUTTON_MIDDLE) _currMouse[SDL_MOUSECODE_MIDDLE] = false;
			else if (event.button.button == SDL_BUTTON_RIGHT) _currMouse[SDL_MOUSECODE_RIGHT] = false;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) _wheel = 1;
			else _wheel = -1;
			break;
		}
	}
}

bool Input::keyDown(SDL_Scancode key) {
	return (!_prevKeyboard[key] && _currKeyboard[key]);
}

bool Input::keyUp(SDL_Scancode key) {
	return (_prevKeyboard[key] && !_currKeyboard[key]);
}

bool Input::keyHold(SDL_Scancode key) {
	return (_currKeyboard[key]);
}

bool Input::mouseMovement() {
	return _mouseMotion;
}

bool Input::mouseDown(SDL_Mousecode button) {
	return (!_prevMouse[button] && _currMouse[button]);
}

bool Input::mouseUp(SDL_Mousecode button) {
	return (_prevMouse[button] && !_currMouse[button]);
}

bool Input::mouseHold(SDL_Mousecode button) {
	return _currMouse[button];
}

int Input::wheelDir() {
	return _wheel;
}

#pragma region Getters/Setters

Vector2<int> Input::getMousePos() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	return Vector2<int>(mouseX, mouseY);
}

#pragma endregion


void Input::makeDataCopy(){
	for (int i = 0; i < _numKeys; ++i) _prevKeyboard[i] = _currKeyboard[i];
	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i) _prevMouse[i] = _currMouse[i];
	_mouseMotion = false;
	_wheel = 0;
}
