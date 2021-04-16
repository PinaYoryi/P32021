#include "Audio.h"
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

FMOD::Channel** Audio::playSound(const std::string name) {
    FMOD::Channel* channel;
    FMOD_RESULT result = _system->playSound(getInstance()->getSound(name), nullptr, false, &channel);
    return nullptr;
}

void Audio::stopSound(FMOD::Channel* channel) {
    FMOD_RESULT result = channel->stop();
    if (result != FMOD_RESULT::FMOD_OK)
        std::cout << "Error: " << result << std::endl;
    delete channel;
}

FMOD::Sound* Audio::getSound(const std::string name) {
    //FMOD_RESULT result = 
    return nullptr;
}

//https://documentation.help/FMOD-Ex/fmod_result.html