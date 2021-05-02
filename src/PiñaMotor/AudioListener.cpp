#include "AudioListener.h"

AudioListener::AudioListener() {

}

void AudioListener::set3DAtributes(Vector3<float> position, Vector3<float> velocity)
{
    _system = Audio::GetInstance()->getSystemFMOD();
  
    p.x = 0;
    p.y = 0;
    p.z = 0;

    v.x = 0;
    v.y = 0;
    v.z = 0;

    f.x = 0;
    f.y = 0;
    f.z = 0;

    u.x = 0;
    u.y = 0;
    u.z = 0;

    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &p, &v, &f, &u);
}

void AudioListener::update() {
    if (_system != nullptr)
        _system->set3DListenerAttributes(0, &p, &v, &f, &u);
  
}
