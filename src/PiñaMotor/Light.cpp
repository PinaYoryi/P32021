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

Vector4<> Light::getAttenuation() {
	Ogre::Vector4 val = _light->getAttenuation();
	return Vector4<>(val.x, val.y, val.z, val.w);
}

Vector4<> Light::getLightDiffuse() {
	Ogre::ColourValue val = _light->getDiffuseColour();
	return Vector4<>(val.r, val.g, val.b, val.a);
}

Vector4<> Light::getLightAmbient() {
	Ogre::ColourValue val = _light->getSpecularColour();
	return Vector4<>(val.r, val.g, val.b, val.a);
}

Light::LightType Light::getProjectionType() {

}

void Light::Render() {
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_lightNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_lightNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_lightNode->setOrientation(tr->rotation());
	}
}
