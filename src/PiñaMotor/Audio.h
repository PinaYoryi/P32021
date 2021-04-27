#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

class Audio {
public:
	Audio();
	static Audio* getInstance();
	void init();
	void update();

	FMOD::Channel* playSound(const char* name, float volume, bool loop);
	void stopSound(FMOD::Channel* channel);

	void setVolume(float volume) const;

	void fadeIn();
	void fadeOut();
	void setPitch(float i);
	void togglePause();

	FMOD::Sound* getSound(const char* name);
	const float getVolume() const;

	FMOD::System* getSystemFMOD() { return _system; }

private:
	
	~Audio();

	void errorCheck(FMOD_RESULT result);


	static Audio* _audioInstance;
	FMOD::System* _system;
	FMOD::ChannelGroup* _channelGroup;
	FMOD::Channel* _channel;
	FMOD_RESULT _result;

	// Lista con todos los sonidos del juego
	std::map<const char*, FMOD::Sound*> _sounds;
};