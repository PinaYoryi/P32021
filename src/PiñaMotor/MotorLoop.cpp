#include "MotorLoop.h"
#include <time.h>
#include "Input.h"
#include "BulletInstance.h"
#include <OgreRoot.h>
#include "Audio.h"

MotorLoop* MotorLoop::_singleton = nullptr;

MotorLoop::~MotorLoop() {
    delete Input::GetInstance();
}

MotorLoop* MotorLoop::GetInstance() {
	return _singleton;
}

bool MotorLoop::Init() {
    Input::Init();
	if (_singleton != nullptr) return false;
	_singleton = new MotorLoop(); return true;
}

#pragma region Loop

void MotorLoop::startLoop() {
	if (_loop == true) return;
	_loop = true;
	_accumulatedTime = 0;
	while (_loop) {
		std::vector<Entity*> ent = SceneManager::GetInstance()->getEntities();
		stepInput();
		stepFixedUpdate(ent);
		stepUpdate(ent);
		stepRender(ent);
		OgreMotor::GetInstance()->getRoot()->renderOneFrame();
	}
}

void MotorLoop::stopLoop() {
	_loop = false;
}

void MotorLoop::stepInput() {
    Input::GetInstance()->update();
}

void MotorLoop::stepUpdate(std::vector<Entity*> ent) {
    for (Entity* e : ent)
        e->update();
}

void MotorLoop::stepFixedUpdate(std::vector<Entity*> ent) {
	updateTime();
	while (_accumulatedTime > FIXED_UPDATE_TIME) {
		for (Entity* e : ent)
			e->fixedUpdate();
        BulletInstance::GetInstance()->update();
		Audio::GetInstance()->update();
		_accumulatedTime -= FIXED_UPDATE_TIME;
	}
}

void MotorLoop::stepRender(std::vector<Entity*> ent) {
    for (Entity* e : ent)
        e->render();
}

void MotorLoop::updateTime() {
	int currentTime = clock();
	_deltaTime = (currentTime - _lastTime) / (float)CLOCKS_PER_SEC;
	_accumulatedTime += _deltaTime;
	_lastTime = currentTime;
}
#pragma endregion