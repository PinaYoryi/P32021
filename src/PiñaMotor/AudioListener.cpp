#include "AudioListener.h"

AudioListener::AudioListener(Vector3<float> position, Vector3<float> velocity) {

    _system = Audio::GetInstance()->getSystemFMOD();

    _position.x = position.x;
    _position.y = position.y;
    _position.z = position.z;

    _velocity.x = velocity.x;
    _velocity.y = velocity.y;
    _velocity.z = velocity.z;
    
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &FMOD_VECTOR(_position), &FMOD_VECTOR(_velocity),&FMOD_VECTOR(_forward),&FMOD_VECTOR(_up));
}

void AudioListener::update() {
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &FMOD_VECTOR(_position), &FMOD_VECTOR(_velocity), &FMOD_VECTOR(_forward), &FMOD_VECTOR(_up));
}
