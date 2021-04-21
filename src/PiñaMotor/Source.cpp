#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include "BulletInstance.h"
#include "MotorLoop.h"
#include "Input.h"
#include "OgreMotor.h"
/// TEST MOTOR OGRE
#include <OgreCamera.h>         
#include <OgreRenderWindow.h>   
#include <OgreViewport.h>        
#include <OgreColourValue.h>    
#include <OgreLight.h>
#include "OgreEntity.h"

#include "Renderer.h"
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Animation.h"
#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
    //Ogre::Root* root;
    //root = new Ogre::Root();
    ////TODO: carne de canon de macro
    //ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    //Entity* ent = new Entity();

    //SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_Window* window = SDL_CreateWindow("Juegaso", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
    //Input* example = Input::getInstance();
    //while (!example->keyDown(SDL_SCANCODE_ESCAPE)) {
    //    example->update();
    //    if (example->keyDown(SDL_SCANCODE_SPACE)) cout << "Primer frame que se pulsa el espacio\n";
    //    if (example->keyHold(SDL_SCANCODE_SPACE)) cout << "Se sigue pulsando el espacio\n";
    //    if (example->keyUp(SDL_SCANCODE_SPACE)) cout << "Se ha dejado de pulsar el espacio\n";
    //    if (example->mouseDown(SDL_MOUSECODE_LEFT)) cout << "Primer frame que se hace click\n";
    //    if (example->mouseHold(SDL_MOUSECODE_LEFT)) cout << "Se sigue haciendo click\n";
    //    if (example->mouseUp(SDL_MOUSECODE_LEFT)) cout << "Se ha dejado de hacer click\n";
    //    if (example->wheelDir() == 1) cout << "La rueda se mueve hacia arriba\n";
    //    if (example->wheelDir() == -1) cout << "La rueda se mueve hacia abajo\n";
    //}
    //SDL_DestroyWindow(window);
    //SDL_Quit();

    OgreMotor app("Motor de Ogre");
    try {
        app.initApp();

        //Inicialización test, cambia el color del viewport a naranja coral
        Ogre::Camera* cam = app.getSceneManager()->createCamera("Main");
        cam->setNearClipDistance(1);
        cam->setFarClipDistance(10000);
        cam->setAutoAspectRatio(true);

        Ogre::SceneNode* camNode = app.getSceneManager()->getRootSceneNode()->createChildSceneNode("Cam");
        camNode->attachObject(cam);
        camNode->setPosition(0, 0, 1000);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

        Ogre::Viewport* vp = app.getRenderWindow()->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(255.0/255.0, 127.0/250.0, 80.0/250.0));

        Ogre::Light* luz = app.getSceneManager()->createLight("Luz");
        luz->setType(Ogre::Light::LT_DIRECTIONAL);
        luz->setDiffuseColour(0.0, 0.0, 0.0);

        Ogre::SceneNode* lightNode = app.getSceneManager()->getRootSceneNode()->createChildSceneNode("Luz");
        lightNode->attachObject(luz);
        lightNode->setDirection(Ogre::Vector3(0, -1, -1));

        
       

        app.getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));
        //Aquí acaba el test

        //Empieza el test del componente renderer
        ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
        ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
        Entity* ent = new Entity();
        ent->addComponent<Renderer>();
        ent->getComponent<Transform>()->setScale({ 20,20,20 });
        while (true) {
            app.getRoot()->renderOneFrame();
            Vector3<float> v = ent->getComponent<Transform>()->position();
            ent->render();
            //ent->getComponent<Transform>()->setPosition(v.x+1.0f, v.y, v.z);
        }
    }
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
    }
    app.closeApp();

    /*delete example;
    delete root;*/

    return 0;
}
