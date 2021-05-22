#include "Audio.h"
#include "fmod_errors.h"
#include <iostream>
#include <fmod_errors.h>
#include <thread>
#include <cstdio>
#include <conio.h>

Audio* Audio::_audioInstance = nullptr;

Audio::Audio() {

	_result = FMOD::System_Create(&_system);
	errorCheck(_result);
	_result = _system->init(128, FMOD_INIT_NORMAL, 0);
	_result = _system->set3DSettings(1.0,DISTANCE_FACTOR, 1.0f);
	_result = _system->set3DNumListeners(1);
	errorCheck(_result);
	_result = _system->getMasterChannelGroup(&_channelGroup);
	errorCheck(_result);
	_sounds = std::map<const char*, FMOD::Sound*>();
}

Audio::~Audio() {
	for (auto sound : _sounds)
		sound.second->release();

	const auto _result = _system->release();
	errorCheck(_result);	
}

Audio* Audio::GetInstance() {
	return _audioInstance;
}

bool Audio::Init() {

	if (_audioInstance != nullptr) return false;
	_audioInstance = new Audio();
	_audioInstance->initResources();
	return true;
}

void Audio::initResources() {
	try {
		_result = FMOD::System_Create(&_system);
		errorCheck(_result);
		_result = _system->init(128, FMOD_INIT_NORMAL, 0);
		_result = _system->getMasterChannelGroup(&_channelGroup);
		errorCheck(_result);
		_sounds = std::map<const char*, FMOD::Sound*>();
	}
	catch (std::exception& e) {
		throw e.what();
	}
}

void Audio::update() {
	try {
		_system->update();
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}


void Audio::stopSound(FMOD::Channel* channel) {
	try {
		_result = channel->stop();
		errorCheck(_result);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	delete channel;
}


FMOD::Sound* Audio::getSound(const char* name) {
	return _sounds[name];
}

void Audio::addSound(){

}

void Audio::errorCheck(FMOD_RESULT result) {
	if (result != FMOD_RESULT::FMOD_OK)
		throw std::exception(FMOD_ErrorString(result));
}

//https://documentation.help/FMOD-Ex/fmod_result.html