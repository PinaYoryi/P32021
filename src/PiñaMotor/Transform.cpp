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
	setPosition(_position.x + x, _position.y + y, _position.z + z);
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo) {
	// Esto no se si estar� bien.
	Quaternion rot(Quaternion::Euler({ xAngle, yAngle, zAngle }));
	switch (relativeTo) {
	case Space::Self:
		setLocalRotation(_localRotation * rot);
		break;
	case Space::Parent:
		if (parent()) {
			setRotation(rot * _rotation);
			break;
		}
	case Space::World:
		if (parent()) {
			setRotation(_rotation * rot * parent()->rotation() );
		}
		else 
			setRotation(_rotation * rot );
		break;
	default:
		break;
	}
}

Transform* Transform::findChild(char* name) {
	for (auto c : _vChild) {
		if (c->getEntity()->getName() == name)
			return c;
	}
	return nullptr;
}

void Transform::setParent(Transform* parent) {
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
		return  q * parent()->rotation();
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
