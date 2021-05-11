#include "BasicAI.h"
#include "Entity.h"

bool BasicAI::init(const std::map<std::string, std::string>& mapa) {
	// Checks de lua

	_transform = getEntity()->getComponent<Transform>();

	_rigidbody = getEntity()->getComponent<Rigidbody>();

	_posObjetivo = Vector3<>(0, 100, 0);

	_rotObjetivo = Vector3<>(0, 0, 0);

	_moveFlag = _rotFlag = true;

	_step = 10;

	return true;
}

void BasicAI::fixedUpdate() {
	// Movimiento
	if (_moveFlag) {
		if (_transform->position() == _posObjetivo) {
			_moveFlag = false;
		}
		else {
			Vector3<> direction = (_posObjetivo - _transform->position()).normalized();
			direction *= _step;
			_rigidbody->addForce(direction, _transform->position());
		}
	}
	// Rotación
	if (_rotFlag) {
		if (Quaternion::Euler(_rotObjetivo) == _transform->rotation()) {
			_rotFlag = false;
		}
		else {
			_transform->rotate(_rotObjetivo.x, _rotObjetivo.y, _rotObjetivo.z);
		}
	}
}

void BasicAI::MoveTo(Vector3<> obj) {
	_posObjetivo = obj;
	_moveFlag = true;
}

void BasicAI::RotateTo(Vector3<> obj) {
	_rotObjetivo = obj;
	_rotFlag = true;
}