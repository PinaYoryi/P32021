#pragma once
#include "Component.h"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include "Vector4.h"

class Light : public Component {
public:
	// An�logos a los tipos de Ogre
	enum LightType { Point, Directional, Spotlight };	
	
	Light() {};
	~Light();
	bool init(const std::map<std::string, std::string>& mapa) override;

	LightType getType();

	float getLinearAttenuation() { return _light->getAttenuationLinear(); }
	float getConstantAttenuation() { return _light->getAttenuationConstant(); }
	float getQuadraticAttenuation() { return _light->getAttenuationQuadric(); }

	Vector4<> getAttenuation() { return _light->getAttenuation(); }

	bool getCastShadows() { return _light->getCastShadows(); }

	Vector4<> getLightDiffuse() { return _light->getDiffuseColour(); }
	Vector4<> getLightSpecular() { return _light->getSpecularColour(); }

	float getSpotlightInnerAngle() { return _light->getSpotlightInnerAngle().valueDegrees();  };
	float getSpotlightOuterAngle() { return _light->getSpotlightOuterAngle().valueDegrees(); };

	void setType(LightType type);

	/// <summary>
	/// Pone la atenuaci�n de la luz de punto
	/// </summary>
	/// <param name="att">El vector 4 con el rango de la luz y las atenuaciones constante, lineal y cuadr�ticas</param>
	void setAttenuation(Vector4<> att);

	void setCastShadows(bool toggle) { _light->setCastShadows(toggle); }

	void setLightDiffuse(Vector4<> diff);
	void setLightSpecular(Vector4<> diff);

	void setSpotlightInnerAngle(float deg);
	void setSpotlightOuterAngle(float deg);
protected:
	void render() override;

	Ogre::Light* _light;
	Ogre::SceneNode* _lightNode;
private:
};