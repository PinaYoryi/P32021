#include "BasicAI.h"
#include "Entity.h"

bool BasicAI::init(const std::map<std::string, std::string>& mapa) {
	// Checks de lua

	_transform = getEntity()->getComponent<Transform>();

	_rigidbody = getEntity()->getComponent<Rigidbody>();

	_posObjetivo = Vector3<>(-10, 4.96, 0);

	_rotObjetivo = Vector3<>(0, 90, 0);

	_moveFlag = _rotFlag = true;

	_threshold = 1.5;

	_step = 25;

	return true;
}

void BasicAI::fixedUpdate() {
	// Movimiento
	if (_moveFlag) {
		if ((_posObjetivo - _transform->position()).magnitude() < _threshold) {
			_moveFlag = false;
			_rigidbody->setLinearVelocity(Vector3<>(0, 0, 0));
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
			//_transform->setRotation(_rotObjetivo.x, _rotObjetivo.y, _rotObjetivo.z);
			btTransform trans;
			_rigidbody->getbT()->getMotionState()->getWorldTransform(trans);
			trans.setRotation(Quaternion::Euler(_rotObjetivo));
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