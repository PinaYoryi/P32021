#include "BasicAI.h"
#include "Entity.h"
#include "OgreMotor.h"
#include <OgreRoot.h>

bool BasicAI::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("step") == mapa.end() || mapa.find("threshold") == mapa.end() || mapa.find("thresholdRot") == mapa.end() || mapa.find("stepRot") == mapa.end()) return false;

	_transform = getEntity()->getComponent<Transform>();

	_rigidbody = getEntity()->getComponent<Rigidbody>();

	_moveFlag = _rotFlag = false;

	std::string s = mapa.at("threshold");
	_threshold = std::stof(s);

	s = mapa.at("thresholdRot");
	_thresholdRot = std::stof(s);

	s = mapa.at("stepRot");
	_velRotation = std::stof(s);

	s = mapa.at("step");
	_step = std::stof(s);

	_initialized = true;

	return true;
}

void BasicAI::fixedUpdate() {
	// Movimiento
	if (_moveFlag) { 
		if ((_posObjetivo - _transform->position()).magnitude() < _threshold) {
			_moveFlag = false;
			if(!_rigidbody->isKinematic())
				_rigidbody->setLinearVelocity(Vector3<>(0, 0, 0)); 
			
		}
		else {
			Vector3<> direction = (_posObjetivo - _transform->position()).normalized();
			if (!_rigidbody->isKinematic()) {
				direction *= _step;
				_rigidbody->addForce(direction, Vector3<>(0, 0, 0));
			}
			else {
				_rigidbody->setPosition(_transform->position() + direction / 3);
				//va muy rapido, por eso lo divido entre 3
			}
		}
	}
	// Rotacion
	if (_rotFlag) {

		if (_t>=1) {
			_rotFlag = false;
			_t = 0;
			 btTransform trans;
			 _rigidbody->getbT()->getMotionState()->getWorldTransform(trans);
			 _rotIni = trans.getRotation();
		}
		else {
			btTransform trans;
			_t += _velRotation;
			_rigidbody->setRotation(Quaternion::Slerp((_rotIni), _rotObjetivo,_t, _thresholdRot));
			_rigidbody->getbT()->getMotionState()->getWorldTransform(trans);
		}
	}
}

void BasicAI::moveTo(Vector3<> obj) {
	_posObjetivo = obj;
	_moveFlag = true;
	//RotateTo(obj);
}

void BasicAI::rotateTo(Vector3<> obj) {	
	_rotFlag = true;
	_rotIni = _transform->rotation();

	Vector3<> dir = obj - _transform->position();
	float angle = atan2(dir.x, dir.z);

	_rotObjetivo = { (float)cos(angle / 2), 0.0f, (float)sin(angle / 2), 0.0f };
#if (defined _DEBUG)
	std::cout << "INICIAL: " << _rotIni.toEuler() << "\n";
	std::cout << "OBJETIVO: " << _rotObjetivo << "\n";
#endif
}