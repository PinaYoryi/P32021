#include <time.h>
#include "MotorLoop.h"

MotorLoop* MotorLoop::_singleton = nullptr;

MotorLoop* MotorLoop::getInstance() {
	if (_singleton == nullptr) {
		_singleton = new MotorLoop();
#ifdef _DEBUG
		std::cout << "Nueva instancia del bucle\n";
#endif

	}
#ifdef _DEBUG
	else std::cout << "Misma instancia del bucle\n";
#endif

	return _singleton;
}

#pragma region Entidades

bool MotorLoop::addEntity() {
	//Comprueba si existe la entidad.
	//Si existe, return false.
	//Si no existe, la a�ade y return true.
	return true;
}

bool MotorLoop::removeEntity() {
	//Comprueba si existe la entidad.
	//Si existe, la quita y return true.
	//Si no existe, return false.
	return true;
}

#pragma endregion

#pragma region Loop

void MotorLoop::startLoop() {
	if (_loop == true) return;
	initLoop();
	while (_loop) {
		stepInput();
		stepFixedUpdate();
		stepUpdate();
		stepRender();
#ifdef _DEBUG
		std::cout << "Iteracion del bucle\n";
#endif
	}
#ifdef _DEBUG
	std::cout << "Detenido bucle\n";
#endif
}

void MotorLoop::stopLoop() {
	_loop = false;
}

void MotorLoop::initLoop() {
	_loop = true;
	_accumulatedTime = 0;
	_lastTime = clock();
#ifdef _DEBUG
	std::cout << "Inicializando bucle\n";
#endif
}

bool MotorLoop::stepInput() {
	//for (Entidad en lista) e->input();
	return true;
}

bool MotorLoop::stepUpdate() {
	//for (Entidad en lista) e->update();
	return true;
}

bool MotorLoop::stepFixedUpdate() {
	updateTime();
	while (_accumulatedTime > FIXED_UPDATE_TIME) {
		//for (Entidad en lista) e->fixedUpdate();
		_accumulatedTime -= FIXED_UPDATE_TIME;
	}
	return true;
}

bool MotorLoop::stepRender() {
	//for (Entidad en lista) e->render();
	return true;
}

void MotorLoop::updateTime() {
	int currentTime = clock();
	_deltaTime = (currentTime - _lastTime) / (float)CLOCKS_PER_SEC;
	_accumulatedTime += _deltaTime;
	_lastTime = currentTime;
}

#pragma endregion