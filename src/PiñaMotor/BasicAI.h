#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"

class BasicAI : public Component{
public:
	BasicAI() {};

	bool init(const std::map<std::string, std::string>& mapa) override;

	void fixedUpdate() override;

	void MoveTo(Vector3<> obj);
	
	void RotateTo(Vector3<> obj);
protected:
	Transform* _transform;
	
	Rigidbody* _rigidbody;

	Vector3<> _posObjetivo;

	Vector3<> _rotObjetivo;

	bool _moveFlag, _rotFlag;

	float _threshold;

	float _step;
};

