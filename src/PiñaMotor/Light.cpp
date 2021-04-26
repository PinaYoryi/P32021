#include "Light.h"
#include "OgreMotor.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

Light::Light() {

}

bool Light::init(const std::map<std::string, std::string>& mapa) {
	_light = OgreMotor::GetInstance()->getSceneManager()->createLight("lightName");
	_lightNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("lightNode"/*_myEntity->getName()*/);
	_lightNode->attachObject(_light);


	// Quitar cuando tengamos inicializacion
	setNearClipPlane(0.1);
	setFarClipPlane(10000);
	setAspectRatio(true);

	return true;
}

Vector4<> Light::getAttenuation() 
{
	Ogre::Vector4 val = _light->getAttenuation();
	return Vector4<>(val.x, val.y, val.z, val.w);
}

void Light::Render() {
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_camNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_camNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_camNode->setOrientation(tr->rotation());
	}
}
