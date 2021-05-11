#include "AudioSource.h"
#include "fmod_errors.h"

AudioSource::AudioSource() {

}

AudioSource::~AudioSource() {
	stopSound();
}

bool AudioSource::init(const std::map<std::string, std::string>& mapa) {
	_system = Audio::GetInstance()->getSystemFMOD();
	_result = Audio::GetInstance()->getResult();
	_channel = nullptr;
	_sound = nullptr;

	return true;
}

void AudioSource::update()
{
	try {
		_system->update();
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void AudioSource::playSound2D(const std::string name, float volume, bool loop) {
	try {
		//_system = Audio::GetInstance()->getSystemFMOD();
		//_result = Audio::GetInstance()->getResult();
		FMOD::Sound* sound;
		_result = _system->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound);
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

void AudioSource::playSound3D(const std::string name, float volume, bool loop, Vector3<float> position, Vector3<float> velocity) {
	_position = (FMOD_VECTOR)position;
	_velocity = (FMOD_VECTOR)velocity;
	try {
		FMOD::Sound* sound;
		_result = _system->createSound(name.c_str(), FMOD_3D, 0, &sound);
		errorCheck(_result);

		_result = sound->set3DMinMaxDistance(0.5f * DISTANCE_FACTOR, 5000.0f * DISTANCE_FACTOR);
		errorCheck(_result);

		_result = _system->playSound(sound, 0, false, &_channel);
		errorCheck(_result);

		_result = _channel->set3DAttributes(&_position, &_velocity);
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


void AudioSource::stopSound() {
	try {
		_result = _channel->stop();
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	// delete _channel;
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


void AudioSource::errorCheck(FMOD_RESULT result) {
	if (result != FMOD_RESULT::FMOD_OK)
		throw std::exception(FMOD_ErrorString(result));
}