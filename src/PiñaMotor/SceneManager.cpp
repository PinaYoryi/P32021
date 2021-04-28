#include "SceneManager.h"


//PRUEBA
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


SceneManager* SceneManager::_singleton = nullptr;

SceneManager::~SceneManager() {
    deleteEntities(true);
}

SceneManager* SceneManager::GetInstance() {
	return _singleton;
}

bool SceneManager::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new SceneManager(); return true;
}

bool SceneManager::addEntity(Entity* ent, bool permanent) {
	std::vector<Entity*>* vec = &_entities;
	if (permanent) vec = &_permanentEntities;
	auto it = find(vec->begin(), vec->end(), ent);
	if (it != vec->end()) return false;
	vec->push_back(ent); return true;
}

bool SceneManager::removeEntity(Entity* ent, bool permanent) {
	std::vector<Entity*>* vec = &_entities;
	if (permanent) vec = &_permanentEntities;
	auto it = find(vec->begin(), vec->end(), ent);
	if (it == vec->end()) return false;
	vec->erase(it);
}

std::vector<Entity*> SceneManager::getEntities() {
	std::vector<Entity*> list;
	list.reserve(_entities.size() + _permanentEntities.size());
	list.insert(list.end(), _entities.begin(), _entities.end());
	list.insert(list.end(), _permanentEntities.begin(), _permanentEntities.end());
	return list;
}

void SceneManager::deleteEntities(bool all) {
    for (Entity* e : _entities) delete e;
    if (all) for (Entity* p : _permanentEntities) delete p;
}

bool SceneManager::loadScene() {
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cp3;

    Entity* camera = new Entity();
    camera->addComponent<Camera>();
    camera->getComponent<Camera>()->setNearClipPlane(1);
    camera->getComponent<Camera>()->setFarClipPlane(10000);
    camera->getComponent<Camera>()->setAspectRatio(true);
    camera->getComponent<Transform>()->setPosition(0, 50, 1000);
    camera->getComponent<Transform>()->setRotation(0, 0, 0);
    camera->getComponent<Camera>()->setBackgroundColor(1.0f, 0.5f, 0.3137f);
    SceneManager::GetInstance()->addEntity(camera);

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

    Entity* ent = new Entity();
    ent->addComponent<Renderer>();
    ent->getComponent<Transform>()->setScale({ 100,0.51,10 });
    ent->getComponent<Transform>()->setPosition({ 0, 0, 0 });
    ent->addComponent<Rigidbody>();
    Rigidbody* rg = ent->getComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ent);
    rg->setStatic(true);

    Entity* ent2 = new Entity();
    ent2->addComponent<Renderer>();
    ent2->addComponent<Animation>();
    Animation* an = ent2->getComponent<Animation>();
    OgreMotor::GetInstance()->addInputListener(an);
    an->changeAnimation("Dance");
    ent2->getComponent<Transform>()->setScale({ 10,10,10 });
    ent2->getComponent<Transform>()->setPosition({ 0, 50, 0 });
    ent2->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ent2);

    Entity* ent3 = new Entity();
    ent3->addComponent<Renderer>();
    ent3->getComponent<Transform>()->setScale({ 10,10,10 });
    ent3->getComponent<Transform>()->setPosition({ 100, 300, 0 });
    ent3->getComponent<Transform>()->setRotation(90, 0, 0);
    ent3->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ent3);

    return true;
}