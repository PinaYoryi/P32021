#pragma once
#include "Component.h"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include "Vector4.h"

class Light : public Component
{
public:
	enum LightType { Point, Directional, Spotlight };
	Light();
	bool init(const std::map<std::string, std::string>& mapa) override;

	float getLinearAttenuation() { return _light->getAttenuationLinear(); }
	float getConstantAttenuation() { return _light->getAttenuationConstant(); }
	float getQuadraticAttenuation() { return _light->getAttenuationQuadric(); }
	Vector4<> getAttenuation();
	bool getCastShadows() { return _light->getCastShadows(); }
	Vector4<> getLightDiffuse();
	Vector4<> getLightAmbient();
	LightType getProjectionType();

	/*void setNearClipPlane(float clip) { _light->setNearClipDistance(clip); }
	void setFarClipPlane(float clip) { _light->setFarClipDistance(clip); }
	void setAspectRatio(bool autoAspectRatio, float aspectRatio = 1.0f);
	void setFOVY(float fov);
	void setProjectionType(ProjectionType type);
	void setViewport(Vector2<> pos, Vector2<> size);
	void setBackgroundColor(Vector3<> color);
	void setBackgroundColor(float r, float g, float b);*/
protected:
	void Render() override;

	Ogre::Light* _light;
	Ogre::SceneNode* _lightNode;
};