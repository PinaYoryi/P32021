#include "MotorLoop.h"
#include <time.h>
#include "Input.h"

//PRUEBA
#include <OgreRoot.h>
#include "Transform.h"
#include "ComponentFactoryRegistration.h"

#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreColourValue.h>
#include <OgreLight.h>
#include "OgreEntity.h"
#include "OgreInstance.h"

#include "Renderer.h"
#include "Animation.h"

MotorLoop* MotorLoop::_singleton = nullptr;
OgreMotor* MotorLoop::_ogre = nullptr;

MotorLoop::~MotorLoop() {
    delete _ent; //<------Esto es placeholder de la escena que crea SceneManager
    delete Input::GetInstance();
}

MotorLoop* MotorLoop::GetInstance() {
	return _singleton;
}

bool MotorLoop::Init(OgreMotor* ogre) {
	_ogre = ogre;
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
		_ogre->getRoot()->renderOneFrame();
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
    _ent->render();
	return true;
}

void MotorLoop::updateTime() {
	int currentTime = clock();
	_deltaTime = (currentTime - _lastTime) / (float)CLOCKS_PER_SEC;
	_accumulatedTime += _deltaTime;
	_lastTime = currentTime;
}




void MotorLoop::placeholderScene() {
    //Inicialización test, cambia el color del viewport a naranja coral
    Ogre::Camera* cam = _ogre->getSceneManager()->createCamera("Main");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);

    Ogre::SceneNode* camNode = _ogre->getSceneManager()->getRootSceneNode()->createChildSceneNode("Cam");
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 1000);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

    Ogre::Viewport* vp = _ogre->getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(255.0 / 255.0, 127.0 / 250.0, 80.0 / 250.0));

    Ogre::Light* luz = _ogre->getSceneManager()->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.0, 0.0, 0.0);

    Ogre::SceneNode* lightNode = _ogre->getSceneManager()->getRootSceneNode()->createChildSceneNode("Luz");
    lightNode->attachObject(luz);
    lightNode->setDirection(Ogre::Vector3(0, -1, -1));

    _ogre->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));

    //Empieza el test del componente renderer
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm3;
    _ent = new Entity();
    _ent->addComponent<Renderer>();
    _ent->addComponent<Animation>();
    _ent->getComponent<Transform>()->setScale({ 20,20,20 });
    Animation* an = _ent->getComponent<Animation>();
    _ogre->addInputListener(an);
    int i = 1;
    an->changeAnimation("Dance");

        /*if (i % 250 == 0)
            an->changeAnimation(std::vector<std::string> { "RunBase", "RunTop" });
        else if (i % 200 == 0)
            an->setLoop(false);
        i++;*/
}

#pragma endregion