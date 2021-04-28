#include "Initialize.h"
#include "MotorLoop.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "SceneManager.h"

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
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
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
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
    }
}
void Initialize::stopBullet() {
    delete BulletInstance::GetInstance();
}
#pragma endregion


#pragma region FMOD
void Initialize::startFMOD() {
    //FMOD.initApp();
}
void Initialize::stopFMOD() {
    //FMOD.closeApp();
}
#pragma endregion