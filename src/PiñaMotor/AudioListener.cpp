#include "AudioListener.h"
#include"fmod_errors.h"
#include "Entity.h"

AudioListener::AudioListener() { }

bool AudioListener::init(const std::map<std::string, std::string>& mapa) {
    if (mapa.find("position") == mapa.end()) return false;
    
    _system = Audio::GetInstance()->getSystemFMOD();
    _result = Audio::GetInstance()->getResult();

    std::string s = mapa.at("position");
    std::string::size_type sz = 0, sa = 0;
    float a = std::stof(s, &sz);
    std::string temp = s.substr(sz + 1);
    float b = std::stof(temp, &sa);
    float c = std::stof(s.substr(sz + sa + 2));
    _p = { a, b, c };
    
    _v = { 0,0,0 };
    _f = { 0,0,1 };  
    _u = { 0,1,0 };

    _trans = _myEntity->getComponent<Transform>();

    if (!_trans->isInitialized())return false;

    set3DAtributes(_p, _v);
    _initialized = true;

    return true;
}

void AudioListener::set3DAtributes(FMOD_VECTOR position, FMOD_VECTOR velocity) {
    _p.x = position.x;
    _p.y = position.y;
    _p.z = position.z;

     if (_system != nullptr) {
         _result = _system->set3DListenerAttributes(0, &_p, &_v, &_f, &_u);
         errorCheck(_result);
     }
}

void AudioListener::update() {
 
    _p = _trans->position();

    if (_system != nullptr) {
        _result = _system->set3DListenerAttributes(0, &_p, &_v, &_f, &_u);
        errorCheck(_result);
    }
    _result = _system->update();
    errorCheck(_result);
  
}

void AudioListener::errorCheck(FMOD_RESULT result) {
    if (result != FMOD_RESULT::FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}
