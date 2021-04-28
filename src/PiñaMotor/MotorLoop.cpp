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
#include "Rigidbody.h"
#include "BulletInstance.h"

MotorLoop* MotorLoop::_singleton = nullptr;

MotorLoop::~MotorLoop() {
    delete Input::GetInstance();
    delete _camera;
    delete _ent;
    delete _ent2;
    delete _ent3;
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
    if (Input::GetInstance()->keyDown(SDL_SCANCODE_SPACE)) {
        _ent2->getComponent<Rigidbody>()->addForce({ 0,200000,0 });
    }

    else if (Input::GetInstance()->keyDown(SDL_SCANCODE_A)) {
        _ent2->getComponent<Rigidbody>()->addForce({ -100000,0,0 });

    }
    else if (Input::GetInstance()->keyDown(SDL_SCANCODE_D)) {
        _ent2->getComponent<Rigidbody>()->addForce({ 100000,0,0 });
    }
	return true;
}

bool MotorLoop::stepUpdate() {
	return true;
}

bool MotorLoop::stepFixedUpdate() {
	updateTime();
	while (_accumulatedTime > FIXED_UPDATE_TIME) {
        BulletInstance::GetInstance()->update();
		_accumulatedTime -= FIXED_UPDATE_TIME;
	}
	return true;
}

bool MotorLoop::stepRender() {
    _camera->render();
    _ent->render();
    _ent2->render();
    _ent3->render();
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
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cp3;

    _camera = new Entity();
    _camera->addComponent<Camera>();
    _camera->getComponent<Camera>()->setNearClipPlane(1);
    _camera->getComponent<Camera>()->setFarClipPlane(10000);
    _camera->getComponent<Camera>()->setAspectRatio(true);

    _camera->getComponent<Transform>()->setPosition(0, 50, 1000);
    _camera->getComponent<Transform>()->setRotation(0, 0, 0);

    _camera->getComponent<Camera>()->setBackgroundColor(1.0f, 0.5f, 0.3137f);
    //Aquí acaba el test

    Ogre::Light* luz = OgreMotor::GetInstance()->getSceneManager()->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(1.0, 1.0, 0.0);

    Ogre::SceneNode* lightNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("Luz");
    lightNode->attachObject(luz);
    lightNode->setDirection(Ogre::Vector3(0, -1, 0));


    //Aquí acaba el test
    OgreMotor::GetInstance()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));

    //Empieza el test del componente renderer
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Rigidbody> cpm4;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm3;

    _ent = new Entity();
    _ent->addComponent<Renderer>();
    _ent->getComponent<Transform>()->setScale({ 100,0.51,10 });
    _ent->getComponent<Transform>()->setPosition({ 0, 0, 0 });
    _ent->addComponent<Rigidbody>();
    Rigidbody* rg = _ent->getComponent<Rigidbody>();
    rg->setStatic(true);

    _ent2 = new Entity();
    _ent2->addComponent<Renderer>();
    _ent2->addComponent<Animation>();
    Animation* an = _ent2->getComponent<Animation>();
    OgreMotor::GetInstance()->addInputListener(an);
    an->changeAnimation("Dance");
    _ent2->getComponent<Transform>()->setScale({ 10,10,10 });
    _ent2->getComponent<Transform>()->setPosition({ 0, 50, 0 });
    _ent2->addComponent<Rigidbody>();

    _ent3 = new Entity();
    _ent3->addComponent<Renderer>();
    _ent3->getComponent<Transform>()->setScale({ 10,10,10 });
    _ent3->getComponent<Transform>()->setPosition({ 100, 300, 0 });
    _ent3->getComponent<Transform>()->setRotation(90, 0, 0);
    _ent3->addComponent<Rigidbody>();
}

#pragma endregion