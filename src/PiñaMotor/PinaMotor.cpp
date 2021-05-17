#include "PinaMotor.h"
#include "MotorLoop.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "SceneManager.h"
#include "Audio.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Gui.h"

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
        Gui* gui = Gui::GetInstance();

        //Hay que pasar por parametro de init el nombre de loadScheme, imagen y visibilidad del raton
        //De momento estan puestos para prueba
        gui->loadScheme("VanillaSkin", "VanillaSkin.scheme");
        gui->setFont("RichStyle.ttf");
        gui->setMouseImage("VanillaSkin/MouseArrow");
        gui->setMouseVisibility(true);
    }
    catch (...) { return false; }
    return true;
}

bool PinaMotor::launch(std::string sceneName) {
    try {
        SceneManager::GetInstance()->loadScene(sceneName);
        MotorLoop::GetInstance()->startLoop();
    }
    catch (...) { return false; }
    return true;
}

void PinaMotor::close() {
    //Se borran en orden inverso al de creación, excepto scenemanager, porque se deben
    //borrar primero las referencias a cuerpos en bullet y despues las entidades que los poseen.
    if (SceneManager::GetInstance() != nullptr) delete SceneManager::GetInstance();
    if (Input::GetInstance() != nullptr) delete Input::GetInstance();
    if (ResourceManager::GetInstance() != nullptr) delete ResourceManager::GetInstance();
    if (MotorLoop::GetInstance() != nullptr) delete MotorLoop::GetInstance();
    if (Audio::GetInstance() != nullptr) delete Audio::GetInstance();
    if (BulletInstance::GetInstance() != nullptr) delete BulletInstance::GetInstance();
    if (OgreMotor::GetInstance() != nullptr) OgreMotor::Close();
}