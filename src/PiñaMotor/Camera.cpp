#include "Camera.h"
#include "OgreMotor.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include "MotorLoop.h"

Camera::Camera() : _cam(nullptr), _camNode(nullptr), _viewport(nullptr) {

}

Camera::~Camera()
{
	OgreMotor::GetInstance()->getSceneManager()->destroySceneNode(_camNode);
	OgreMotor::GetInstance()->getSceneManager()->destroyCamera(_myEntity->getName());
	OgreMotor::GetInstance()->getRenderWindow()->removeAllViewports();
}

bool Camera::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("near") == mapa.end() || mapa.find("far") == mapa.end() || mapa.find("autoaspect") == mapa.end() || mapa.find("aspect") == mapa.end() ||
		mapa.find("fov") == mapa.end() || mapa.find("proyection") == mapa.end() || mapa.find("viewport") == mapa.end() || mapa.find("color") == mapa.end()) return false;
	std::string name = _myEntity->getName() /*+ to_string(MotorLoop::GetInstance()->getTotalTimeRunning())*/;
	_cam = OgreMotor::GetInstance()->getSceneManager()->createCamera(name);
	_camNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	////if(OgreMotor::GetInstance()->getSceneManager()->getCurrentViewport())
	//	OgreMotor::GetInstance()->getRenderWindow()->removeAllViewports(); //removeViewport(OgreMotor::GetInstance()->getSceneManager()->getCurrentViewport()->getZOrder());

	_viewport = OgreMotor::GetInstance()->getRenderWindow()->addViewport(_cam);
	_camNode->attachObject(_cam);

	std::string s = mapa.at("near");
	setNearClipPlane(std::stof(s));

	s = mapa.at("far");
	setFarClipPlane(std::stof(s));

	bool b;
	s = mapa.at("autoaspect");
	if (s == "true") b = true;
	else if (s == "false") b = false;
	else return false;

	s = mapa.at("aspect");
	setAspectRatio(b, std::stof(s));

	s = mapa.at("fov");
	setFOVY(Ogre::Math::DegreesToRadians(std::stof(s)));

	s = mapa.at("proyection");
	setProjectionType((Camera::ProjectionType)(std::stoi(s)));

	s = mapa.at("viewport");
	std::string::size_type sz = 0, sa = 0, sb = 0;
	float a = std::stof(s, &sz);
	float be = std::stof(s.substr(sz + 1), &sa);
	float c = std::stof(s.substr(sz + sa + 2), &sb);
	float d = std::stof(s.substr(sz + sa + sb + 3));
	setViewport({a, be }, { c, d });

	s = mapa.at("color");
	setBackgroundColor({ std::stof(s, &sz), std::stof(s.substr(sz + 1), &sa), std::stof(s.substr(sz + sa + 2)) });
	_initialized = true;

	return true;
}

Camera::ProjectionType Camera::getProjectionType() {
	return (Camera::ProjectionType)_cam->getProjectionType();
}

void Camera::setAspectRatio(bool autoAspectRatio, float aspectRatio) {
	if (!autoAspectRatio) {
		_cam->setAspectRatio(aspectRatio);
	}
	else {
		_cam->setAutoAspectRatio(autoAspectRatio);
	}
}

void Camera::setFOVY(float fov) {
	_cam->setFOVy(Ogre::Radian(fov));
}

void Camera::setProjectionType(Camera::ProjectionType type) {
	_cam->setProjectionType((Ogre::ProjectionType)type);
}

void Camera::setViewport(Vector2<> pos, Vector2<> size) {
	_viewport->setDimensions(pos.x, pos.y, size.x, size.y);
}

void Camera::setBackgroundColor(Vector3<> color) {
	_viewport->setBackgroundColour(Ogre::ColourValue(color.x, color.y, color.z));
}

void Camera::setBackgroundColor(float r, float g, float b) {
	setBackgroundColor({ r, g, b });
}

void Camera::render() {
	if (!_active) return;
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_camNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_camNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_camNode->setOrientation(tr->rotation());
	}
}
