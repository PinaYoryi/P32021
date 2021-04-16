#include "Camera.h"
#include "OgreInstance.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"

Camera::Camera()
{
	//_camNode = new Node()
	_cam
}

void Camera::Render()
{
	Transform* tr;
	if (tr = _myEntity->getComponent<Transform>() != nullptr) {
		_camNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_camNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_camNode->setOrientation(tr->rotation());
	}
}
