#include "AudioListener.h"




AudioListener::AudioListener(Vector3<float> position, Vector3<float> velocity){
    FMOD_RESULT result = FMOD::System_Create(&_system);
    if (result != FMOD_RESULT::FMOD_OK)
        std::cout << "Error: " << result << std::endl;

    _position.x = position.getX();
    _position.y = position.getY();
    _position.z = position.getZ();

    _velocity.x = velocity.getX();
    _velocity.y = velocity.getY();
    _velocity.z = velocity.getZ();
    
    _system->set3DListenerAttributes(0, &_position, &_velocity,&_forward,&_up);
}

void AudioListener::update()
{
    _system->set3DListenerAttributes(0, &_position, &_velocity, &_forward, &_up);
}
