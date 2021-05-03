#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

const float DISTANCE_FACTOR=1;

class Audio {
public:

	Audio();

	static Audio* GetInstance();

	static bool Init();

	void update();

	~Audio();

	/// <summary>
	/// 
	/// </summary>
	void stopSound(FMOD::Channel* channel);

	/// <summary>
	/// Devuelve un sonido del map
	/// </summary>
	FMOD::Sound* getSound(const char* name);

	/// <summary>
	/// Devuelve el system de fmod para utilizarlo en otros archivos(AudioListener/AudioSource).
	/// </summary>
	FMOD::System* getSystemFMOD() { return _system; };

	/// <summary>
	/// Devuelve el result de fmod para utilizarlo en otros archivos(AudioListener/AudioSource).
	/// </summary>
	 FMOD_RESULT getResult() { return _result; }

	 void addSound();

private:
	void initResources();

	void errorCheck(FMOD_RESULT result);


	static Audio* _audioInstance;
	FMOD::System* _system;
	FMOD::ChannelGroup* _channelGroup;
	FMOD::Channel* _channel;
	FMOD_RESULT _result;

	// Lista con todos los sonidos del juego
	std::map<const char*, FMOD::Sound*> _sounds;
};