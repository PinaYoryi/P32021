#pragma once
#include "Component.h"
#include <fmod.hpp>
#include <map>
#include "Vector3.h"
#include "Audio.h"

class AudioSource : public Component {
public:
	AudioSource();
	~AudioSource() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void playSound2D(const std::string name);
	void pauseSound(const std::string name);
	void stopSound(const std::string name);

	// Añade un nuevo sonido a la lista
	void addNewSound(const std::string name);
	void createSound3D(char* name);

	void setPosition(Vector3<float> position) { _position.x = position.x; _position.y = position.y; _position.z = position.z; };
	Vector3<float> getPosition() { return Vector3<float>(_position.x, _position.y, _position.z); };

private:
	
	FMOD_VECTOR _position;
	FMOD_VECTOR _velocity;
	FMOD::System* _system;
	Audio* _instance;
	FMOD::Sound* _sound;
	// Lista con los canales de sonido que se estan ejecutando
	std::map<std::string, FMOD::Channel*> _sounds;
};