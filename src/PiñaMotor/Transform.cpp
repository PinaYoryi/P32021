#include "Transform.h"
#include "Entity.h"
#include <string>
#include "SceneManager.h"

bool Transform::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("position") == mapa.end() || mapa.find("rotation") == mapa.end() || mapa.find("scale") == mapa.end() || mapa.find("parent") == mapa.end()) return false;
	std::string::size_type sz = 0, sa = 0;

	std::string s = mapa.at("position");
	float a = std::stof(s, &sz);
	string temp = s.substr(sz + 1);
	float b = std::stof(temp, &sa);
	float c = std::stof(s.substr(sz + sa + 2));
	_localPosition = { a, b, c };

	std::string s2 = mapa.at("rotation");
	_localRotation = Quaternion::Euler({ std::stof(s2, &sz), std::stof(s2.substr(sz + 1), &sa), std::stof(s2.substr(sz + sa + 2)) });

	std::string s3 = mapa.at("scale");
	_localScale = { std::stof(s3, &sz), std::stof(s3.substr(sz + 1), &sa), std::stof(s3.substr(sz + sa + 2)) };

	std::string s4 = mapa.at("parent");
	if(std::stoi(s4) >= 0)
		setParent(SceneManager::GetInstance()->getEntityByID(std::stoi(s4))->getComponent<Transform>());

	if (_parent == nullptr) {
		_position  = _localPosition;
		_rotation  = _localRotation;
		_scale  = _localScale;
	}
	_initialized = true;
	return true;
}

void Transform::translate(float x, float y, float z) {
	setPosition(_position.x + x, _position.x + y, _position.x + z);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo) {
	// Esto no se si estar� bien.
	Quaternion rot(Quaternion::Euler({ xAngle, yAngle, zAngle }));
	switch (relativeTo) {
	case Space::Self:
		_rotation = _rotation * rot;
		break;
	case Space::Parent:
		_rotation = rot * _rotation;
			break;
	case Space::World:
		getParentData();
		_rotation = _rotation * _localRotation.inverse() * rot * _localRotation;
		break;
	default:
		break;
	}

	_rotation.normalize();
}

Transform* Transform::findChild(char* name) {
	for (auto c : _vChild) {
		if (c->getEntity()->getName() == name)
			return c;
	}
	return nullptr;
}

void Transform::setParent(Transform* parent)
{
	// Si teniamos otro padre, nos quitamos como hijos
	if (_parent != nullptr)
		_parent->removeChild(this);

	// Nos ponemos como hijos del nuevo padre
	if (parent != nullptr)
		parent->setChild(this);

	_parent = parent;
	_position = inverseTransformDirection(_parent->position());
	_rotation = inverseTransformRotation(_parent->rotation());
	_scale = inverseTransformDirection(_parent->scale());
}

void Transform::setPosition(Vector3<float> v) {
	_position = v;
	_localPosition = inverseTransformDirection(v);
}

void Transform::setPosition(float x, float y, float z) {
	_position = { x, y, z };
	_localPosition = inverseTransformDirection(x, y, z);
}

void Transform::setRotation(Quaternion q) {
	_rotation = q;
	_localRotation = inverseTransformRotation(q);
}

Quaternion Transform::inverseTransformRotation(Quaternion q) {
	if (parent())
		return q.conjugate() * parent()->rotation() * q;
	return q;
}

Quaternion Transform::transformRotation(Quaternion q) {
	if (parent())
		return  parent()->rotation() * q;
	return q;
}

void Transform::setRotation(float x, float y, float z) {

	_rotation = Quaternion::Euler({ x, y, z });
	_localRotation = inverseTransformRotation(_rotation);
}

void Transform::setScale(Vector3<float> v) {
	_scale = v;
	_localScale = inverseTransformDirection(v);

	for (auto c : _vChild) {
		c->setScale(v + c->localScale());
	}
}

void Transform::setScale(float x, float y, float z) {
	_scale = { x, y, z };
	_localScale = inverseTransformDirection(x, y, z);

	for (auto c : _vChild) {
		c->setScale(Vector3<float>(x, y, z) + c->localScale());
	}
}

void Transform::setLocalPosition(Vector3<float> v) {
	_localPosition = v;
	_position = transformDirection(v);

	for (auto c : _vChild) {
		c->setPosition(_position + c->localPosition());
	}
}

void Transform::setLocalPosition(float x, float y, float z) {
	_localPosition = { x, y, z };
	_position = transformDirection(x, y, z);

	for (auto c : _vChild) {
		c->setPosition(_position + c->localPosition());
	}
}

void Transform::setLocalRotation(Quaternion q) {
	_localRotation = q;
	_rotation = transformRotation(q);

	for (auto c : _vChild) {
		c->setRotation(_rotation.conjugate() * c->localRotation());
	}
}

void Transform::setLocalRotation(float x, float y, float z) {
	_localRotation = Quaternion::Euler({ x, y, z });
	_rotation = transformRotation(_localRotation);

	for (auto c : _vChild) {
		c->setRotation(_rotation.conjugate() * c->localRotation());
	}
}

void Transform::setLocalScale(Vector3<float> v) {
	_localScale = v;
	_scale = transformDirection(v);

	for (auto c : _vChild) {
		c->setScale(_scale + c->localScale());
	}
}

void Transform::setLocalScale(float x, float y, float z) {
	_localScale = { x, y, z };
	_scale = transformDirection(x, y, z);

	for (auto c : _vChild) {
		c->setScale(_scale + c->localScale());
	}
}

Vector3<float> Transform::transformDirection(Vector3<float> direction) {
	if (_parent == nullptr)
		return direction;

	else
		return { abs(direction.x + _parent->localPosition().x),
				 abs(direction.y + _parent->localPosition().y),
				 abs(direction.z + _parent->localPosition().z) };
}

Vector3<float> Transform::transformDirection(float x, float y, float z) {
	if (_parent == nullptr)
		return { x, y, z };

	else
		return { abs(x + _parent->localPosition().x),
				 abs(y + _parent->localPosition().y),
				 abs(z + _parent->localPosition().z) };
}

Vector3<float> Transform::inverseTransformDirection(Vector3<float> direction) {
	if (_parent == nullptr)
		return direction;

	else
		return { abs(direction.x - _parent->localPosition().x),
				 abs(direction.y - _parent->localPosition().y),
				 abs(direction.z - _parent->localPosition().z) };
}

Vector3<float> Transform::inverseTransformDirection(float x, float y, float z) {
	if (_parent == nullptr)
		return { x, y, z };

	else
		return { abs(x - _parent->localPosition().x),
				 abs(y - _parent->localPosition().y),
				 abs(z - _parent->localPosition().z) };
}

void Transform::getParentData() {
	if(parent()) {
		_rotation  = parent()->rotation() * _localRotation;

		Vector3<> scale;
		scale.x = parent()->localScale().x * _localScale.x;
		scale.y = parent()->localScale().y * _localScale.y;
		scale.z = parent()->localScale().z * _localScale.z;

		_scale = scale;
		_position = parent()->position() + _localPosition;
	}
	else {
		_rotation  = _localRotation;
		_scale  = _localScale;
		_position = _localPosition;
	}
}
