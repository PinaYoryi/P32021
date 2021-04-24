#include "Camera.h"
#include "OgreMotor.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

Camera::Camera()
{

}

bool Camera::init(const std::map<std::string, std::string>& mapa)
{
	_cam = OgreMotor::GetInstance()->getSceneManager()->createCamera("camName");
	_camNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("camNode"/*_myEntity->getName()*/);
	_viewport = OgreMotor::GetInstance()->getRenderWindow()->addViewport(_cam);
	_camNode->attachObject(_cam);


	// Quitar cuando tengamos inicializacion
	setNearClipPlane(0.1); 
	setFarClipPlane(10000);
	setAspectRatio(true);

	return true;
}

Camera::ProjectionType Camera::getProjectionType()
{
	return (Camera::ProjectionType)_cam->getProjectionType();
}

void Camera::setAspectRatio(bool autoAspectRatio, float aspectRatio)
{
	if (!autoAspectRatio) {
		_cam->setAspectRatio(aspectRatio);
	}
	else {
		_cam->setAutoAspectRatio(autoAspectRatio);
	}
}

void Camera::setFOVY(float fov)
{
	_cam->setFOVy(Ogre::Radian(fov));
}

void Camera::setProjectionType(Camera::ProjectionType type)
{
	_cam->setProjectionType((Ogre::ProjectionType)type);
}

void Camera::setViewport(Vector2<> pos, Vector2<> size)
{
	_viewport->setDimensions(pos.x, pos.y, size.x, size.y);
}

void Camera::setBackgroundColor(Vector3<> color)
{
	_viewport->setBackgroundColour(Ogre::ColourValue(color.x, color.y, color.z));
}

void Camera::setBackgroundColor(float r, float g, float b)
{
	setBackgroundColor({ r, g, b });
}

void Camera::Render()
{
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_camNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_camNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_camNode->setOrientation(tr->rotation());
	}
}
