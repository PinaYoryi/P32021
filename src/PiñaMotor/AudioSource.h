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
	
	void playSound2D(const char* name, float volume, bool loop);
	void playSound3D(const char* name, float volume, bool loop);
	void pauseSound(const char* name);
	void stopSound(const char* name);
	void fadeIn();
	void fadeOut();

	// Añade un nuevo sonido a la lista
	void addNewSound(const char* name);
	void createSound3D(char* name);

	void setPosition(Vector3<float> position) { _position.x = position.x; _position.y = position.y; _position.z = position.z; };
	Vector3<float> getPosition() { return Vector3<float>(_position.x, _position.y, _position.z); };

private:
	
	void errorCheck(FMOD_RESULT result);

	Vector3<float> _position;
	Vector3<float> _velocity;
	FMOD::System* _system;
	FMOD_RESULT _result;
	FMOD::Sound* _sound;

	// Lista con los canales de sonido que se estan ejecutando
	//std::map<const char*, FMOD::Sound*> _sounds;



	FMOD::Channel* _channel;
};