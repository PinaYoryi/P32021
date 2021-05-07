#pragma once
#include "Transform.h"

class PlayerController : public Component {
public:
	PlayerController();

	/// <summary>
	/// Inicializa el componente con los valores pasador por parametro
	/// utiliza setMesh para poner su mesh y setMaterial para poner su material
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Mueve el componente cámara de la entidad que tiene esta clase en
	/// base a los movimientos del raton
	/// </summary>
	void update() override;

protected:
	Transform* _trans;
	float _pitch, _yaw, _sensibility;;
};