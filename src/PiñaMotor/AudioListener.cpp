#include "AudioListener.h"
#include"fmod_errors.h"

AudioListener::AudioListener() {

}

void AudioListener::set3DAtributes(Vector3<float> position, Vector3<float> velocity)
{
    _system = Audio::GetInstance()->getSystemFMOD();
    _result= Audio::GetInstance()->getResult();

    p.x = 0;
    p.y = 0;
    p.z = 0;

    v.x = -(0.2 * 1 / 33.33);
    v.y = 0;
    v.z = 0;

    f.x = 0;
    f.y = 0;
    f.z = 1;

    u.x = 0;
    u.y = 1;
    u.z = 0;

     if (_system != nullptr) {
         _result = _system->set3DListenerAttributes(0, &p, &v, &f, &u);
         errorCheck(_result);
     }
}

void AudioListener::update() {
    p.x += v.x;

    v.x = -(0.2 * 1 / 33.33);
    v.y = 0;
    v.z = 0;
    if (_system != nullptr) {
        _result = _system->set3DListenerAttributes(0, &p, &v, &f, &u);
        errorCheck(_result);
    }
    _result = _system->update();
    errorCheck(_result);
  
}

void AudioListener::errorCheck(FMOD_RESULT result)
{
    if (result != FMOD_RESULT::FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}
