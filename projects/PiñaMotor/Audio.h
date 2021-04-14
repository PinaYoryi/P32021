#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

class Audio
{
public:
	static Audio* getInstance();
	void init();
	void update();

	FMOD::Sound* playSound(const std::string id);
	void stopSound(FMOD::Channel* channel);

	void setVolume(float volume) const;
	const float getVolume() const;

private:
	Audio() {};
	~Audio() {};

	static Audio* _audioInstance;

	// Lista con todos los sonidos del juego
	std::map<std::string, FMOD::Sound*> _sounds;
};