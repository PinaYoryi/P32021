#pragma once
#include "Component.h"
#include <fmod.hpp>
#include <map>

class AudioSource : public Component {
public:
	AudioSource() {};
	~AudioSource() {};

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void playSound(const std::string name);
	void pauseSound(const std::string name);
	void stopSound(const std::string name);

	// Añade un nuevo sonido a la lista
	void addNewSound(const std::string name);

private:
	// Lista con los canales de sonido que se estan ejecutando
	std::map<std::string, FMOD::Channel*> _sounds;
};