#include "AudioListener.h"

AudioListener::AudioListener(Vector3<float> position, Vector3<float> velocity){
    _system = Audio::getInstance()->getSystemFMOD();

    _position.x = position.getX();
    _position.y = position.getY();
    _position.z = position.getZ();

    _velocity.x = velocity.getX();
    _velocity.y = velocity.getY();
    _velocity.z = velocity.getZ();
    
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &_position, &_velocity,&_forward,&_up);
}

void AudioListener::update()
{
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &_position, &_velocity, &_forward, &_up);
}
