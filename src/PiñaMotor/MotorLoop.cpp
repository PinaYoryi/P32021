#include "MotorLoop.h"
#include <time.h>
#include "Input.h"

//PRUEBA
#include <OgreRoot.h>
#include "ComponentFactoryRegistration.h"

#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreColourValue.h>
#include <OgreLight.h>

#include "Transform.h"
#include "Renderer.h"
#include "Animation.h"
#include "Camera.h"

MotorLoop* MotorLoop::_singleton = nullptr;

MotorLoop::~MotorLoop() {
	delete _cam; //<------Esto es placeholder de la escena que crea SceneManager TODO:
    delete _ent; //<------Esto es placeholder de la escena que crea SceneManager
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
	initLoop();
	while (_loop) {
		stepInput();
		stepFixedUpdate();
		stepUpdate();
		stepRender();
		OgreMotor::GetInstance()->getRoot()->renderOneFrame();
	}
}

void MotorLoop::stopLoop() {
	_loop = false;
}

void MotorLoop::initLoop() {
	_loop = true;
	_accumulatedTime = 0;
	_lastTime = clock();
    placeholderScene(); //<------Esto es placeholder de la escena que crea SceneManager
}

bool MotorLoop::stepInput() {
    Input::GetInstance()->update();
	return true;
}

bool MotorLoop::stepUpdate() {
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
    _ent->render();
	_cam->render();
	return true;
}

void MotorLoop::updateTime() {
	int currentTime = clock();
	_deltaTime = (currentTime - _lastTime) / (float)CLOCKS_PER_SEC;
	_accumulatedTime += _deltaTime;
	_lastTime = currentTime;
}




void MotorLoop::placeholderScene() {
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
	ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
	ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm3;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cpm4;

    _cam = new Entity();
    _cam->addComponent<Camera>();
    _cam->getComponent<Camera>()->setNearClipPlane(1);
    _cam->getComponent<Camera>()->setFarClipPlane(10000);
    _cam->getComponent<Camera>()->setAspectRatio(true);
    _cam->getComponent<Camera>()->setBackgroundColor(1.0f, 0.5f, 0.3137f);

    _cam->getComponent<Transform>()->setPosition(0, 0, 1000);
    _cam->getComponent<Transform>()->setRotation(0, 0, 0);


    Ogre::Light* luz = OgreMotor::GetInstance()->getSceneManager()->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.0, 0.0, 0.0);

    Ogre::SceneNode* lightNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("Luz");
    lightNode->attachObject(luz);
    lightNode->setDirection(Ogre::Vector3(0, -1, -1));

    OgreMotor::GetInstance()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));

    _ent = new Entity();
	_ent->getComponent<Transform>()->setScale({ 20,20,20 });
	_ent->addComponent<Renderer>();
	_ent->addComponent<Animation>();
    Animation* an = _ent->getComponent<Animation>();
    OgreMotor::GetInstance()->addInputListener(an);
    an->changeAnimation("Dance");
}

#pragma endregion