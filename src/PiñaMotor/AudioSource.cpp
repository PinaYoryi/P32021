#include "AudioSource.h"
#include "fmod_errors.h"


AudioSource::AudioSource() {

	_system = Audio::GetInstance()->getSystemFMOD();
	_result = Audio::GetInstance()->getResult();
	_channel = nullptr;
	_sound = nullptr;
}

void AudioSource::playSound2D(const char* name, float volume, bool loop) {
	try {
		//_system = Audio::GetInstance()->getSystemFMOD();
		//_result = Audio::GetInstance()->getResult();
		FMOD::Sound* sound;
		_result = _system->createSound(name, FMOD_DEFAULT, 0, &sound);
		errorCheck(_result);
		//_sounds[name] = sound;

		_result = _system->playSound(sound, 0, false, &_channel);
		errorCheck(_result);

		_result = _channel->setVolume(volume);
		errorCheck(_result);

		if (loop) {
			_result = _channel->setMode(FMOD_LOOP_NORMAL);
			errorCheck(_result);
		}

		_result = _channel->setPaused(false);
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void AudioSource::playSound3D(const char* name, float volume, bool loop)
{
	try {
		FMOD::Sound* sound;
		_result = _system->createSound(name, FMOD_3D, 0, &sound);
		errorCheck(_result);

		_result = sound->set3DMinMaxDistance(0.5f * DISTANCE_FACTOR, 5000.0f * DISTANCE_FACTOR);

		_result = _system->playSound(sound, 0, false, &_channel);
		errorCheck(_result);

		_result = _channel->set3DAttributes(&FMOD_VECTOR(_position),&FMOD_VECTOR(_velocity));
		errorCheck(_result);

		_result = _channel->setVolume(volume);
		errorCheck(_result);

		if (loop) {
			_result = _channel->setMode(FMOD_LOOP_NORMAL);
			errorCheck(_result);
		}

		_result = _channel->setPaused(false);
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void AudioSource::pauseSound(const char* name) {
	bool paused;
	_channel->getPaused(&paused);
	_channel->setPaused(!paused);
}

void AudioSource::stopSound(const char* name) {
	try {
		_result = _channel->stop();
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	delete _channel;
}

void AudioSource::fadeIn(){
	unsigned long long parentclock;
	_result = _channel->getDSPClock(NULL, &parentclock);
	_result = _channel->addFadePoint(parentclock, 0.0f);
	_result = _channel->addFadePoint(parentclock + 500000, 1.0f);
}

void AudioSource::fadeOut(){
	unsigned long long parentclock;
	_result = _channel->getDSPClock(NULL, &parentclock);
	float vol;
	_channel->getVolume(&vol);
	_result = _channel->addFadePoint(parentclock, vol);
	_result = _channel->addFadePoint(parentclock + 500000, 0.0f);
}

void AudioSource::setPitch(float i){
	try {

		_result = _channel->setPitch(i);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void AudioSource::togglePause(){
	bool paused;
	_channel->getPaused(&paused);
	_channel->setPaused(!paused);
}

void AudioSource::setVolume(float volume) const{
	try {
		const auto _result = _channel->setVolume(volume);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

float AudioSource::getVolume(){
	float volume;
	try {
		const auto _result = _channel->getVolume(&volume);
		return volume;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 0;
	}
}

void AudioSource::addNewSound(const char* name) {

}

void AudioSource::createSound3D(char* name ) {
    FMOD_RESULT result = _system->createSound(name, (FMOD_MODE)(FMOD_3D), 0, &_sound);
    if (result != FMOD_OK){
       (result);
    }
}

void AudioSource::errorCheck(FMOD_RESULT result) {
	if (result != FMOD_RESULT::FMOD_OK)
		throw std::exception(FMOD_ErrorString(result));
}