#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"

class BasicAI : public Component{
public:
	BasicAI() {};

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
	void MoveTo(Vector3<> obj);
	
	/// <summary>
	/// Marca el flag para rotar y pone la rotacion con la que debe acabar
	/// </summary>
	void RotateTo(Vector3<> obj);
protected:
	Transform* _transform;	
	Rigidbody* _rigidbody;

	//posicion objetivo
	Vector3<> _posObjetivo;
	//rotacion objetivo
	Vector3<> _rotObjetivo;

	//bools que si son true se mueve/rota 
	bool _moveFlag, _rotFlag;

	//umbral de la distancia objetivo (margen de error)
	float _threshold;


	float _step;

	//umbral de la rotaicon objetivo (margen de error)
	float _thresholdRot;
	Quaternion _rotIni;
	float _t;
	float _velRotation;

};

