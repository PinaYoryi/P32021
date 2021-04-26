#include "Initialize.h"

Initialize::Initialize() {
    startOgre();
    startBullet();
    startFMOD();

    //SceneManager::Init();
    //SceneManager::loadScene();

    MotorLoop::Init(_ogre); //<---- Hay que pasar los motores
    MotorLoop::GetInstance()->startLoop();
}

Initialize::~Initialize() {
    stopOgre();
    stopBullet();
    stopFMOD();

    delete _ogre;
    delete MotorLoop::GetInstance();
}


#pragma region Ogre
void Initialize::startOgre() {
    _ogre = new OgreMotor("Motor de Ogre");
    try {
        _ogre->initApp();
    }
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
    }
}

void Initialize::stopOgre() {
    _ogre->closeApp();
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