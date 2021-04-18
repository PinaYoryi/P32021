#include "Audio.h"
#include "fmod_errors.h"
#include <iostream>

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