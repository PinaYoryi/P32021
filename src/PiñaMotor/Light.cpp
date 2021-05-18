#include "Light.h"
#include "OgreMotor.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

Light::~Light()
{
	OgreMotor::GetInstance()->getSceneManager()->destroySceneNode(_lightNode);
	OgreMotor::GetInstance()->getSceneManager()->destroyLight(_myEntity->getName()); 
}

bool Light::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("type") == mapa.end() || mapa.find("attenuation") == mapa.end() || mapa.find("shadows") == mapa.end() || mapa.find("diffuse") == mapa.end() ||
		mapa.find("specular") == mapa.end() || mapa.find("spotinner") == mapa.end() || mapa.find("spotouter") == mapa.end() ) return false;

	_light = OgreMotor::GetInstance()->getSceneManager()->createLight(_myEntity->getName());
	_lightNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	_lightNode->attachObject(_light);

	std::string s = mapa.at("type");
	if(s != "") setType((Light::LightType)(std::stoi(s)));

	s = mapa.at("attenuation");
	if (s != "") {
		std::string::size_type sz = 0, sa = 0, sb = 0;
		float a = std::stof(s, &sz);
		float b = std::stof(s.substr(sz + 1), &sa);
		float c = std::stof(s.substr(sz + sa + 2), &sb);
		float d = std::stof(s.substr(sz + sa + sb + 3));
		setAttenuation({a, b, c, d});
	}

	bool shadows;
	s = mapa.at("shadows");
	if (s == "true") shadows = true;
	else if (s == "false") shadows = false;
	else return false;
	setCastShadows(shadows);

	s = mapa.at("diffuse");
	if (s != "") {
		std::string::size_type sz = 0, sa = 0, sb = 0;
		float a = std::stof(s, &sz);
		float b = std::stof(s.substr(sz + 1), &sa);
		float c = std::stof(s.substr(sz + sa + 2), &sb);
		float d = std::stof(s.substr(sz + sa + sb + 3));
		setLightDiffuse({ a, b, c, d });
	}

	s = mapa.at("specular");
	if (s != "") {
		std::string::size_type sz = 0, sa = 0, sb = 0;
		float a = std::stof(s, &sz);
		float b = std::stof(s.substr(sz + 1), &sa);
		float c = std::stof(s.substr(sz + sa + 2), &sb);
		float d = std::stof(s.substr(sz + sa + sb + 3));
		setLightSpecular({ a, b, c, d });
	}

	s = mapa.at("spotinner");
	if(s != "") setSpotlightInnerAngle(std::stof(s));

	s = mapa.at("spotouter");
	if (s != "") setSpotlightOuterAngle(std::stof(s));

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
	if (!_active) return;
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_lightNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_lightNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_lightNode->setOrientation(tr->rotation());
	}
}
