#include "Initialize.h"
#include "MotorLoop.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "SceneManager.h"
#include "Audio.h"

Initialize::Initialize() {
    startOgre();
    startBullet();
    startFMOD();

    SceneManager::Init();
    SceneManager::GetInstance()->loadScene();

    MotorLoop::Init();
    MotorLoop::GetInstance()->startLoop();
}

Initialize::~Initialize() {
    stopOgre();
    stopBullet();
    stopFMOD();
    delete MotorLoop::GetInstance();
    delete SceneManager::GetInstance();
}

#pragma region Ogre
void Initialize::startOgre() {
    try {
        OgreMotor::Init("Motoraso");
    }
    catch (const std::exception&) {
        throw "Fallo Ogre";
    }
}

void Initialize::stopOgre() {
    OgreMotor::Close();
}
#pragma endregion


#pragma region Bullet
void Initialize::startBullet() {
    try {
        BulletInstance::Init();
    }
    catch (const std::exception&){
        throw "Fallo Bullet";
    }
}
void Initialize::stopBullet() {
    delete BulletInstance::GetInstance();
}
#pragma endregion


#pragma region FMOD
void Initialize::startFMOD() {
    try{
        Audio::Init();
    }
    catch (const std::exception&){
        throw "Fallo FMOD";
    }
   
}
void Initialize::stopFMOD() {
    delete Audio::GetInstance();
}
#pragma endregion