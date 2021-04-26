#include "AudioSource.h"


AudioSource::AudioSource()
{
	_system = Audio::getInstance()->getSystemFMOD();
}

void AudioSource::playSound(const std::string name) {

}

void AudioSource::pauseSound(const std::string name) {

}

void AudioSource::stopSound(const std::string name) {

}

void AudioSource::addNewSound(const std::string name) {

}

void AudioSource::createSound3D(char* name )
{
    FMOD_RESULT result = _system->createSound(name, (FMOD_MODE)(FMOD_3D), 0, &_sound);
    if (result != FMOD_OK)
    {
       (result);
    }
}
