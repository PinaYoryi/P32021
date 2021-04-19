#include "Audio.h"
#include "fmod_errors.h"
#include <iostream>
#include <fmod_errors.h>
#include <thread>
#include <cstdio>
#include <conio.h>

Audio* Audio::_audioInstance = nullptr;

Audio* Audio::getInstance()
{
    if (_audioInstance == nullptr) {
        _audioInstance = new Audio();
    }
    return _audioInstance;
}

void Audio::init() {
    FMOD_RESULT result = FMOD::System_Create(&_system);
    if (result != FMOD_RESULT::FMOD_OK)
        std::cout << "Error: " << result << std::endl;
}

void Audio::update()
{
    _system->update();
}

FMOD::Channel* Audio::playSound(const std::string name, float volume, bool loop) {
    FMOD::Channel* channel;
    try {
        FMOD_RESULT result = _system->playSound(getInstance()->getSound(name), nullptr, false, &channel);
        errorCheck(result);

        result = channel->setVolume(volume);
        errorCheck(result);

        if (loop) {
            result = channel->setMode(FMOD_LOOP_NORMAL);
            errorCheck(result);
        }

        result = channel->setPaused(false);
        errorCheck(result);
        return channel;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
}

void Audio::stopSound(FMOD::Channel* channel) {
    FMOD_RESULT result = channel->stop();
    if (result != FMOD_RESULT::FMOD_OK)
        std::cout << "Error: " << result << std::endl;
    delete channel;
}

void Audio::fadeIn()
{
    unsigned long long parentclock;
    FMOD_RESULT res = _channel->getDSPClock(NULL, &parentclock);
    res = _channel->addFadePoint(parentclock, 0.0f);
    res = _channel->addFadePoint(parentclock + 500000, 1.0f);
}

void Audio::fadeOut()
{
    unsigned long long parentclock;
    FMOD_RESULT res = _channel->getDSPClock(NULL, &parentclock);
    float vol;
    _channel->getVolume(&vol);
    res = _channel->addFadePoint(parentclock, vol);
    res = _channel->addFadePoint(parentclock + 500000, 0.0f);
}

void Audio::setPitch(float i)
{
    FMOD_RESULT result;
    result = _channel->setPitch(i);
    if (result != FMOD_OK) {
        std::cout << FMOD_ErrorString(result) << std::endl;
        //exit(-1);
    }
}

void Audio::togglePause()
{
    bool paused;
    _channel->getPaused(&paused);
    _channel->setPaused(!paused);
}

void Audio::setVolume(float volume) const {
}

FMOD::Sound* Audio::getSound(const std::string name) {
    return _sounds[name];
}

const float Audio::getVolume() const {
    return 0.0f;
}

void Audio::errorCheck(FMOD_RESULT result) {
    if (result != FMOD_RESULT::FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}

//https://documentation.help/FMOD-Ex/fmod_result.html