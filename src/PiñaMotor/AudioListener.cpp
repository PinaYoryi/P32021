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
        _system->set3DListenerAttributes(0, &_position, &_velocity,&_forward,&_up);
}

void AudioListener::update() {
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &_position, &_velocity, &_forward, &_up);
}
