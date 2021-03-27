#include <time.h>
#include "MotorLoop.h"

MotorLoop* MotorLoop::singleton_ = nullptr;

MotorLoop* MotorLoop::getInstance() {
	if (singleton_ == nullptr) {
		singleton_ = new MotorLoop();
		std::cout << "Nueva instancia del bucle\n";
	}
	else std::cout << "Misma instancia del bucle\n";
	return singleton_;
}

//----------
//Métodos Lista Entidades
//----------

bool MotorLoop::addEntity() {
	//Comprueba si existe la entidad.
	//Si existe, return false.
	//Si no existe, la añade y return true.
	return true;
}

bool MotorLoop::removeEntity() {
	//Comprueba si existe la entidad.
	//Si existe, la quita y return true.
	//Si no existe, return false.
	return true;
}

//----------
//Métodos Loop
//----------

void MotorLoop::startLoop() {
	if (loop_ == true) return;
	initLoop();
	while (loop_) {
		stepInput();
		stepFixedUpdate();
		stepUpdate();
		stepRender();
		std::cout << "Iteracion del bucle\n";
		stopLoop();
	}
	std::cout << "Detenido bucle\n";
}

void MotorLoop::stopLoop() {
	loop_ = false;
}

void MotorLoop::initLoop() {
	loop_ = true;
	accumulatedTime_ = 0;
	lastTime_ = clock();
	std::cout << "Inicializando bucle\n";
}

bool MotorLoop::stepInput() {
	//for (Entidad en lista) e->input();
	return true;
}

bool MotorLoop::stepFixedUpdate() {
	//for (Entidad en lista) e->fixedUpdate();
	return true;
}

bool MotorLoop::stepUpdate() {
	updateTime();
	while (accumulatedTime_ > UPDATE_TIME) {
		//for (Entidad en lista) e->update();
		accumulatedTime_ -= UPDATE_TIME;
	}
	return true;
}

bool MotorLoop::stepRender() {
	//for (Entidad en lista) e->render();
	return true;
}

void MotorLoop::updateTime() {
	int currentTime = clock();
	deltaTime_ = (currentTime - lastTime_) / (float)CLOCKS_PER_SEC;
	accumulatedTime_ += deltaTime_;
	lastTime_ = currentTime;
}