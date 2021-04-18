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

	FMOD::Channel* playSound(const std::string name, float volume, bool loop);
	void stopSound(FMOD::Channel* channel);

	void setVolume(float volume) const;

	void fadeIn();
	void fadeOut();
	void setPitch(float i);
	void togglePause();

	FMOD::Sound* getSound(const std::string name);
	const float getVolume() const;

private:
	Audio() {};
	~Audio() {};

	void errorCheck(FMOD_RESULT result);

	static Audio* _audioInstance;
	FMOD::System* _system;
	FMOD::Channel* _channel;

	// Lista con todos los sonidos del juego
	std::map<std::string, FMOD::Sound*> _sounds;
};