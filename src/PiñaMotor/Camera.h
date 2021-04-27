#pragma once
#include "Component.h"
#include <OgreCamera.h>
#include "Vector3.h"
#include "Vector2.h"

class Camera :
	public Component
{
public:
	enum ProjectionType { Perspective, Orthographic };
	Camera();
	bool init(const std::map<std::string, std::string>& mapa) override;

	float getNearClipPlane() { return _cam->getNearClipDistance(); }
	float getFarClipPlane() { return _cam->getFarClipDistance(); }
	float getAspectRatio() { return _cam->getAspectRatio(); }
	float getFOVY() { return _cam->getFOVy().valueDegrees(); }
	ProjectionType getProjectionType();

	void setNearClipPlane(float clip) { _cam->setNearClipDistance(clip); }
	void setFarClipPlane(float clip) { _cam->setFarClipDistance(clip); }
	void setAspectRatio(bool autoAspectRatio, float aspectRatio = 1.0f);
	void setFOVY(float fov);
	void setProjectionType(ProjectionType type);
	void setViewport(Vector2<> pos, Vector2<> size);
	void setBackgroundColor(Vector3<> color);
	void setBackgroundColor(float r, float g, float b);
protected:
	void render() override;

	Ogre::Viewport* _viewport;
	Ogre::Camera* _cam;
	Ogre::SceneNode* _camNode;
};

