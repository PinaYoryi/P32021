#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"

class BasicAI : public Component{
public:
	BasicAI():_transform(nullptr),_rigidbody(nullptr) {};

	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Mueve a la entidad usando el rigidbody hacia esa posicion
	/// Rota a la entidad usando el rigidbody hacia esa rotacion
	/// utiliza Quaternion::Slerp, por lo que se rota lentamente
	/// </summary>
	void fixedUpdate() override;

	/// <summary>
	/// Marca el flag para mover y pone la posicion destino
	/// </summary>
	void moveTo(Vector3<> obj);

	void setStep(float step) { _step = step; }
	void setStepRot(float velRotation) { _velRotation = velRotation; }
	float getThreshhold() { return _threshold; };

	/// <summary>
	/// Marca el flag para rotar y pone la dirección en la que debe mirar
	/// </summary>
	void rotateTo(Vector3<> obj);

protected:
	Transform* _transform;	
	Rigidbody* _rigidbody;

	//posicion objetivo
	Vector3<> _posObjetivo;
	//rotacion objetivo
	Quaternion _rotObjetivo;

	//bools que si son true se mueve/rota 
	bool _moveFlag=false, _rotFlag = false;

	//umbral de la distancia objetivo (margen de error)
	float _threshold=0;

	// Potencia del movimiento
	float _step=0.1;

	//umbral de la rotaicon objetivo (margen de error)
	float _thresholdRot=0.1;

	Quaternion _rotIni;

	float _t=0;

	float _velRotation=0;
};

