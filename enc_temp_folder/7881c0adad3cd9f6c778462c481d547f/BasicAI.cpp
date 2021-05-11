#include "BasicAI.h"
#include "Entity.h"
#include "Rigidbody.h"

bool BasicAI::init(const std::map<std::string, std::string>& mapa) {
	// Checks de lua

	_transform = getEntity()->getComponent<Transform>();

	_rigidbody = getEntity()->getComponent<Rigidbody>();

	_posObjetivo = Vector3<>(10, 0, 0);

	_rotObjetivo = Vector3<>(0, 90, 0);

	_moveFlag = _rotFlag = true;

	_step = 300;

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
			_rigidbody->addForce(direction, Vector3<>(0, 0, 0));
		}
	}
	// Rotación
	if (_rotFlag) {
		if (Quaternion::Euler(_rotObjetivo) == _transform->rotation()) {
			_rotFlag = false;
		}
		else {
			_rigidbody->rotate(Quaternion::Euler(_rotObjetivo));
		}
	}

	std::cout << _transform->rotation() << "\n";
}

void BasicAI::MoveTo(Vector3<> obj) {
	_posObjetivo = obj;
	_moveFlag = true;
}

void BasicAI::RotateTo(Vector3<> obj) {
	_rotObjetivo = obj;
	_rotFlag = true;
}