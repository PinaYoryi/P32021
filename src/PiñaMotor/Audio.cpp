#include "Audio.h"
#include "fmod_errors.h"
#include <iostream>
#include <fmod_errors.h>
#include <thread>
#include <cstdio>
#include <conio.h>

Audio* Audio::_audioInstance = nullptr;

Audio::Audio() {
    _sounds = std::map<const char*, FMOD::Sound*>();
}

Audio::~Audio() {
    try {
        for (auto sound : _sounds)
            sound.second->release();

        const auto _result = _system->release();
        errorCheck(_result);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

Audio* Audio::getInstance() {
    if (_audioInstance == nullptr) {
        _audioInstance = new Audio();
    }
    return _audioInstance;
}

void Audio::init() {
    try {
        _result = FMOD::System_Create(&_system);
        errorCheck(_result);
        _result = _system->init(128, FMOD_INIT_NORMAL,0);
        _result = _system->getMasterChannelGroup(&_channelGroup);
        errorCheck(_result);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Audio::update() {
    try {
        _result = _system->update();
        errorCheck(_result);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

FMOD::Channel* Audio::playSound(const char* name, float volume, bool loop) {
    //FMOD::Channel* channel;
    try {
        FMOD::Sound* sound;        
        _result = _system->createSound(name, FMOD_DEFAULT, 0, &sound);
        errorCheck(_result);
        _sounds[name]=sound;

        _result = _system->playSound(_sounds[name] ,0, false, &_channel);
        errorCheck(_result);

        _result = _channel->setVolume(volume);
        errorCheck(_result);

        if (loop) {
            _result = _channel->setMode(FMOD_LOOP_NORMAL);
            errorCheck(_result);
        }

        _result = _channel->setPaused(false);
        errorCheck(_result);
        return _channel;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
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

void Audio::fadeIn() {
    unsigned long long parentclock;
    _result = _channel->getDSPClock(NULL, &parentclock);
    _result = _channel->addFadePoint(parentclock, 0.0f);
    _result = _channel->addFadePoint(parentclock + 500000, 1.0f);
}

void Audio::fadeOut() {
    unsigned long long parentclock;
    _result = _channel->getDSPClock(NULL, &parentclock);
    float vol;
    _channel->getVolume(&vol);
    _result = _channel->addFadePoint(parentclock, vol);
    _result = _channel->addFadePoint(parentclock + 500000, 0.0f);
}

void Audio::setPitch(float i) {
    try {
       
        _result = _channel->setPitch(i);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Audio::togglePause() {
    bool paused;
    _channel->getPaused(&paused);
    _channel->setPaused(!paused);
}

void Audio::setVolume(float volume) const {
    try {
        const auto _result = _channelGroup->setVolume(volume);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

FMOD::Sound* Audio::getSound(const char* name) {
    return _sounds[name];
}

const float Audio::getVolume() const {
    float volume;
    try {
        const auto _result = _channelGroup->getVolume(&volume);
        return volume;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

void Audio::errorCheck(FMOD_RESULT result) {
    if (result != FMOD_RESULT::FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}

//https://documentation.help/FMOD-Ex/fmod_result.html