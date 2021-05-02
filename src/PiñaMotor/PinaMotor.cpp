#include "PinaMotor.h"
#include "MotorLoop.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "SceneManager.h"
#include "Audio.h"

PinaMotor::~PinaMotor() {
    //Se borran en orden inverso al de creación, excepto scenemanager, porque se deben
    //borrar primero las referencias a cuerpos en bullet y despues las entidades que los poseen.
    if (MotorLoop::GetInstance() != nullptr) delete MotorLoop::GetInstance();
    if (Audio::GetInstance() != nullptr) delete Audio::GetInstance();
    if (BulletInstance::GetInstance() != nullptr) delete BulletInstance::GetInstance();
    OgreMotor::Close();
    if (SceneManager::GetInstance() != nullptr) delete SceneManager::GetInstance();
}

void PinaMotor::init(std::string windowName) {
    OgreMotor::Init(windowName);
    BulletInstance::Init();
    Audio::Init();
    SceneManager::Init();
    MotorLoop::Init();
}

void PinaMotor::launch(std::string sceneName) {
    SceneManager::GetInstance()->loadScene(sceneName);
    MotorLoop::GetInstance()->startLoop();
}