#include "PinaMotor.h"
#include "MotorLoop.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "SceneManager.h"
#include "Audio.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Gui.h"

#include <string>

bool PinaMotor::init(std::string windowName) {
    try {
        OgreMotor::Init(windowName);
        BulletInstance::Init();
        Audio::Init();
        SceneManager::Init();
        MotorLoop::Init();
        ResourceManager::Init();
        Input::Init();
        Gui::Init();
       
    }
    catch (std::exception e) { 
#if (defined _DEBUG)
        std::cout << e.what();
#endif
        return false;
    }
    return true;
}

bool PinaMotor::launch(std::string sceneName) {
    try {
        SceneManager::GetInstance()->loadComponents();
        SceneManager::GetInstance()->newScene(sceneName);
        SceneManager::GetInstance()->loadEntities();
        MotorLoop::GetInstance()->startLoop();
    }
    catch (std::exception e) {
#if (defined _DEBUG)
        std::cerr << e.what();
#endif
        return false;
    }
    return true;
}

void PinaMotor::close() {
    //Se borran en orden inverso al de creaci�n, excepto scenemanager, porque se deben
    //borrar primero las referencias a cuerpos en bullet y despues las entidades que los poseen.
    if (SceneManager::GetInstance() != nullptr) delete SceneManager::GetInstance();
    if (Gui::GetInstance() != nullptr) delete Gui::GetInstance();
    if (Input::GetInstance() != nullptr) delete Input::GetInstance();
    if (ResourceManager::GetInstance() != nullptr) delete ResourceManager::GetInstance();
    if (MotorLoop::GetInstance() != nullptr) delete MotorLoop::GetInstance();
    if (Audio::GetInstance() != nullptr) delete Audio::GetInstance();
    if (BulletInstance::GetInstance() != nullptr) delete BulletInstance::GetInstance();
    if (OgreMotor::GetInstance() != nullptr) OgreMotor::Close();
}