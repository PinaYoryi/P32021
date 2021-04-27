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
	setType(LightType::Point);
	setLightDiffuse(Vector4<>(1.0, 1.0, 1.0, 1.0));
	setCastShadows(true);

	return true;
}

Light::LightType Light::getType() {
	return (Light::LightType)_light->getType();
}

void Light::setAttenuation(Vector4<> att) {
	_light->setAttenuation(att.x, att.y, att.z, att.w);
}

void Light::setLightDiffuse(Vector4<> diff) {
	_light->setDiffuseColour(diff);
}

void Light::setLightSpecular(Vector4<> diff) {
	_light->setSpecularColour(diff);
}

void Light::setType(LightType type) {
	_light->setType((Ogre::Light::LightTypes)type);
}

void Light::setSpotlightInnerAngle(float deg) {
	_light->setSpotlightInnerAngle(Ogre::Radian(Ogre::Degree(deg)));
}

void Light::setSpotlightOuterAngle(float deg) {
	_light->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(deg)));
}

void Light::render() {
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_lightNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_lightNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_lightNode->setOrientation(tr->rotation());
	}
}
