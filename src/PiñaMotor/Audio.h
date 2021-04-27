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

	/// <summary>
	/// Añade un sonido/musica y lo ejcuta, name es la direccion o nombre del archivo, 
	/// volume el volumen de dicho sonido y loop por si se quiere ejecutar en bucle
	/// </summary>
	FMOD::Channel* playSound(const char* name, float volume, bool loop);

	/// <summary>
	/// 
	/// </summary>
	void stopSound(FMOD::Channel* channel);

	/// <summary>
	/// Cambia el volumen actual por el parametro establecido
	/// </summary>
	void setVolume(float volume) const;

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
	/// Devuelve un sonido del map
	/// </summary>
	FMOD::Sound* getSound(const char* name);

	/// <summary>
	/// Devuelve el volumen actual
	/// </summary>
	const float getVolume() const;

	/// <summary>
	/// Devuelve el system de fmod para utilizarlo en otros archivos(AudioListener/AudioSource).
	/// </summary>
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