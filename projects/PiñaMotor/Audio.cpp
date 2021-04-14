#include "Audio.h"

Audio* Audio::_audioInstance = nullptr;

Audio* Audio::getInstance()
{
    if (_audioInstance == nullptr) {
        _audioInstance = new Audio();
    }
    return _audioInstance;
}