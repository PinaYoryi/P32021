#include "SceneManager.h"
#include "ResourceManager.h"

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
#include "Light.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "Vector3.h"
#include "ResourceManager.h"
#include "Lifetime.h"
#include "BasicAI.h"

#include "PlayerController.h"


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
    delete *it;
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

bool SceneManager::loadScene(std::string sceneName) {
    deleteEntities();
    //std::string scene = ResourceManager::GetInstance()->scene(sceneName);

    //Escena hardcodeada mientras no hay lectura en Lua
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Light> cpl;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cp3;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm4;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<PlayerController> cpm5;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Rigidbody> cpm44;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioSource> cpm54;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<AudioListener> cpm6;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Lifetime> cpm7;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<BasicAI> cpm8;
    
    Entity* jugador = new Entity("Jugador");
    Entity* camera = new Entity("Camara");
    camera->getComponent<Transform>()->setParent(jugador->getComponent<Transform>());
    camera->addComponent<Camera>();
    //camera->addComponent<PlayerController>();
    camera->getComponent<Camera>()->setNearClipPlane(1);
    camera->getComponent<Camera>()->setFarClipPlane(10000);
    camera->getComponent<Camera>()->setAspectRatio(true);
    camera->getComponent<Transform>()->setPosition(0, 1, 50);
    camera->getComponent<Transform>()->setRotation(0, 0, 0);
    camera->getComponent<Camera>()->setBackgroundColor(1.0f, 0.5f, 0.3137f);
    jugador->getComponent<Transform>()->setRotation(0, 0,0 );
    SceneManager::GetInstance()->addEntity(camera);
    SceneManager::GetInstance()->addEntity(jugador);

    Entity* light = new Entity("Luz");
    light->addComponent<Light>();

    Light* lComp = light->getComponent<Light>();
    lComp->setType(Light::LightType::Point);
    lComp->setLightDiffuse(Vector4<>(0.0, 0.3, 1.0, 1.0));
    lComp->setSpotlightInnerAngle(90);
    lComp->setSpotlightOuterAngle(180);
    lComp->setAttenuation(Vector4<>(100, 0.001, 0.001, 0.001));

    light->getComponent<Transform>()->setPosition(0, 20, 0);
    light->getComponent<Transform>()->setRotation(270, 0, 0);
    SceneManager::GetInstance()->addEntity(light);

    OgreMotor::GetInstance()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));


    Entity* ent = new Entity("Suelo");
    ent->getComponent<Transform>()->setScale({ 10, 0.01, 10 });
    ent->addComponent<Renderer>();
    ent->getComponent<Transform>()->setPosition({ 0, 0, 0 });
    ent->getComponent<Transform>()->setRotation(0, 0, 0);
    ent->addComponent<Rigidbody>();
    Rigidbody* rg = ent->getComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ent);
    rg->setStatic(true);

    Entity* ficha = new Entity("Sinbad");
    ficha->getComponent<Transform>()->setScale({ 1, 1, 1 });
    //ficha->getComponent<Transform>()->setRotation(0, 180, 0);
    //ficha->getComponent<Transform>()->setPosition({ 0, 180, 0 });
    //ficha->addComponent<Lifetime>();
    ficha->addComponent<AudioSource>();
    ficha->addComponent<Renderer>();
    ficha->addComponent<Rigidbody>();
    ficha->addComponent<BasicAI>();
    SceneManager::GetInstance()->addEntity(ficha);

    Entity* capsule = new Entity("capsule");
    capsule->addComponent<Renderer>();
    capsule->getComponent<Transform>()->setScale({ 0.01, 0.02, 0.01 });
    capsule->getComponent<Transform>()->setPosition({ 10, 31.0, 4.0 });
    //capsule->getComponent<Transform>()->rotate(90, 0, 0);
    capsule->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(capsule);
    //SceneManager::GetInstance()->removeEntity(capsule);

    /*Entity* ent2 = new Entity("sphere");
    ent2->getComponent<Transform>()->setScale({ 0.1,0.1,0.1});
    ent2->addComponent<Renderer>();
    ent2->getComponent<Transform>()->setPosition({ 0, 180, 0 });
    ent2->addComponent<Rigidbody>();
    ent2->addComponent<AudioListener>();
    ent2->getComponent<AudioListener>()->set3DAtributes(ent2->getComponent<Transform>()->position(), Vector3<float>(0, 0, 0));
    ent2->getComponent<AudioListener>()->setPosition(ent2->getComponent<Transform>()->position());
    ent2->getComponent<AudioListener>()->setVelocity({ (-(0.2 * 1 / 33.33)), 0,0 });
    SceneManager::GetInstance()->addEntity(ent2);*/
    


   /* Entity* ficha2 = new Entity();
    ficha2->addComponent<Renderer>();
    ficha2->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha2->getComponent<Transform>()->setPosition({ -10, 0.0, 0.0 });
    ficha2->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha2);

    Entity* ficha3 = new Entity("Ficha3");
    ficha3->addComponent<Renderer>();
    ficha3->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha3->getComponent<Transform>()->setPosition({ -5, 0.0, 0.0 });
    ficha3->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha3);

    Entity* ficha4 = new Entity("Ficha4");
    ficha4->addComponent<Renderer>();
    ficha4->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha4->getComponent<Transform>()->setPosition({ 0, 0.0, 0.0 });
    ficha4->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha4);

    Entity* ficha5 = new Entity("Ficha5");
    ficha5->addComponent<Renderer>();
    ficha5->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha5->getComponent<Transform>()->setPosition({ 5, 0.0, 0.0 });
    ficha5->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha5);

    /*Entity* ficha6 = new Entity("Ficha6");
    ficha6->addComponent<Renderer>();
    ficha6->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha6->getComponent<Transform>()->setPosition({ 10, 0.0, 0.0 });
    ficha6->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha6);

    Entity* ficha7 = new Entity("Ficha7");
    ficha7->addComponent<Renderer>();
    ficha7->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha7->getComponent<Transform>()->setPosition({ 15, 0.0, 0.0 });
    ficha7->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha7);

    Entity* ficha8 = new Entity("Ficha8");
    ficha8->addComponent<Renderer>();
    ficha8->getComponent<Transform>()->setScale({ 0.01, 0.1, 0.05 });
    ficha8->getComponent<Transform>()->setPosition({ 20, 0.0, 0.0 });
    ficha8->addComponent<Rigidbody>();
    SceneManager::GetInstance()->addEntity(ficha8);*/


    //Entity* ent3 = new Entity();
    //ent3->addComponent<Renderer>();
    //ent3->getComponent<Transform>()->setScale({ 0.1, 0.1, 0.1 });
    //ent3->getComponent<Transform>()->setPosition({ 0, 200, 0 });
    //ent3->getComponent<Transform>()->setRotation(0, 0, 0);
    //ent3->addComponent<Rigidbody>();
    //SceneManager::GetInstance()->addEntity(ent3);

    return true;
}