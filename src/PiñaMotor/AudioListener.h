#pragma once
#include "Component.h"
#include <fmod.hpp>
#include "Vector3.h"
#include "Audio.h"
#include "Transform.h"

class AudioListener : public Component {
public:
	AudioListener();
	~AudioListener() {};

	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	///
	/// </summary>
	void set3DAtributes(FMOD_VECTOR position, FMOD_VECTOR velocity);

	/// <summary>
	/// metodo set para asignar una posicion
	/// </summary>
	void setPosition(Vector3<float> position) { _p.x = position.x; _p.y = position.y; _p.z = position.z;};
	/// <summary>
	/// metodo get para la posicion
	/// </summary>
	Vector3<float> getPosition() { return Vector3<float>(_p.x,_p.y,_p.z); };

	/// <summary>
	/// metodo set para asignar una velocidad
	/// </summary>
	void setVelocity(Vector3<float> velocity) { _v.x = velocity.x; _v.y = velocity.y; _v.z = velocity.z; };
	/// <summary>
	/// metodo get para la velocidad
	/// </summary>
	Vector3<float> getVelocity() { return Vector3<float>(_v.x, _v.y, _v.z); };

	/// <summary>
	/// metodo set para asignar una direccion vertical
	/// </summary>
	void setUp(Vector3<float> up) { _u.x = up.x; _u.y = up.y; _u.z = up.z; };
	/// <summary>
	/// metodo get para una direccion vertical
	/// </summary>
	Vector3<float> getUp() { return Vector3<float>(_u.x, _u.y, _u.z); };

	/// <summary>
	/// metodo set para asignar una direccion horizontal
	/// </summary>
	void setForward(Vector3<float> forward) { _f.x = forward.x; _f.y = forward.y; _f.z = forward.z; };
	/// <summary>
	/// metodo get para una direccion horizontal
	/// </summary>
	Vector3<float> getForward() { return Vector3<float>(_f.x, _f.y, _f.z); };

	virtual void update() override;

private:
	void errorCheck(FMOD_RESULT result);

	FMOD_RESULT _result;
	
	Transform* _trans = nullptr;

	FMOD_VECTOR _p;	// Posición
	
	FMOD_VECTOR _f;	// Forward
	
	FMOD_VECTOR _u;	// Upward
	
	FMOD_VECTOR _v;	// Velocidad
	
	FMOD::System* _system;
};