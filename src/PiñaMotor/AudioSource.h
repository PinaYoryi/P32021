#pragma once
#include "Component.h"
#include <fmod.hpp>
#include <map>
#include "Vector3.h"
#include "Audio.h"



class AudioSource : public Component {
public:
	AudioSource();

	~AudioSource();

	bool init(const std::map<std::string, std::string>& mapa) override;

	
	virtual void update() override;

	/// <summary>
	/// Añade un sonido/musica y lo ejcuta, name es la direccion o nombre del archivo, 
	/// volume el volumen de dicho sonido y loop por si se quiere ejecutar en bucle
	/// </summary>
	void playSound2D(const std::string name, float volume, bool loop);

	/// <summary>
	/// Añade un sonido/musica y lo ejcuta en una posicion en concreto determinada por el parametro position, name es la direccion o nombre del archivo, 
	/// volume el volumen de dicho sonido y loop por si se quiere ejecutar en bucle
	/// </summary>
	void playSound3D(const std::string name, float volume, bool loop, Vector3<float> position, Vector3<float> velocity);

	/// <summary>
	/// para un sonido
	/// </summary>
	void stopSound();

	/// <summary>
	/// Ejecuta un fade in del sonido actual
	/// </summary>
	void fadeIn();

	/// <summary>
	/// Ejecuta un fade out del sonido actual
	/// </summary>
	void fadeOut();

	/// <summary>
	/// Cambia el pitch(velocidad) del sonido actual
	/// </summary>
	void setPitch(float i);

	/// <summary>
	/// Cambia de estado entre pausa, y pausa dicho sonido
	/// </summary>
	void togglePause();

	/// <summary>
	/// Cambia el volumen actual por el parametro establecido
	/// </summary>
	void setVolume(float volume) const;

	/// <summary>
	/// Devuelve el volumen actual
	/// </summary>
	float getVolume();


	void setPosition(Vector3<float> position) { _position.x = position.x; _position.y = position.y; _position.z = position.z; };
	Vector3<float> getPosition() { return Vector3<float>(_position.x, _position.y, _position.z); };

	void setVelocity(Vector3<float> velocity) { _velocity.x = velocity.x; _velocity.y = velocity.y; _velocity.z = velocity.z; };
	Vector3<float> getVelocity() { return Vector3<float>(_velocity.x, _velocity.y, _velocity.z); };

private:
	
	void errorCheck(FMOD_RESULT result);
	FMOD_VECTOR _position;
	FMOD_VECTOR _velocity;
	FMOD::System* _system;
	FMOD_RESULT _result;
	FMOD::Sound* _sound;

	// Lista con los canales de sonido que se estan ejecutando
	//std::map<const char*, FMOD::Sound*> _sounds;

	FMOD::Channel* _channel;
};