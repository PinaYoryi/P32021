#include "Transform.h"
#include "Entity.h"

Transform::Transform(Vector3<float> position, Quaternion rotation, Vector3<float> scale, Transform* parent) :
	_parent(parent), _position(position), _rotation(rotation), _scale(scale) {
	if (parent == nullptr) {
		_localPosition = _position;
		_localRotation = _rotation;
		_localScale = _scale;

	}
	else {
		_localPosition = inverseTransformDirection(parent->position());
		_localRotation = inverseTransformRotation(parent->rotation());
		_localScale = inverseTransformDirection(parent->scale());
	}

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
	_localPosition = inverseTransformDirection(_position);
	_localRotation = inverseTransformRotation(_rotation);
	_localScale = inverseTransformDirection(_scale);
}

void Transform::setPosition(Vector3<float> v) {
	_position = v;
	_localPosition = inverseTransformDirection(v);

	for (auto c : _vChild) {
		c->setPosition(v + c->localPosition());
	}
}

void Transform::setPosition(float x, float y, float z) {
	_position = { x, y, z };
	_localPosition = inverseTransformDirection(x, y, z);

	for (auto c : _vChild) {
		c->setPosition(Vector3<float>(x, y, z) + c->localPosition());
	}
}

void Transform::setRotation(Quaternion q) {
	_rotation = q;
	_localRotation = inverseTransformRotation(q);

	for (auto c : _vChild) {
		c->setRotation(q * c->localRotation() * q.conjugate());
	}
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

	for (auto c : _vChild) {
		c->setRotation(_rotation * c->localRotation());
	}
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
		_localRotation = parent()->rotation() * _rotation;

		Vector3<> scale;
		scale.x = parent()->scale().x * _scale.x;
		scale.y = parent()->scale().y * _scale.y;
		scale.z = parent()->scale().z * _scale.z;

		_localScale = scale;
		_localPosition = parent()->position() + _position;
	}
	else {
		_localRotation = _rotation;
		_localScale = _scale;
		_localPosition = _position;
	}
}
