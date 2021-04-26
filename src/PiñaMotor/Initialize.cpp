#include "Initialize.h"
#include "OgreMotor.h"
#include "MotorLoop.h"

Initialize::Initialize() {
    startOgre();
    startBullet();
    startFMOD();

    //SceneManager::Init();
    //SceneManager::loadScene();

    MotorLoop::Init();
    MotorLoop::GetInstance()->startLoop();
}

Initialize::~Initialize() {
    delete MotorLoop::GetInstance();
    stopOgre();
    stopBullet();
    stopFMOD();
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
    //bullet.initApp();
}
void Initialize::stopBullet() {
    //bullet.closeApp();
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