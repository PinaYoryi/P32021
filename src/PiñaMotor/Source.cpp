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
#include "OgreInstance.h"
#include "Camera.h"
#include "OgreEntity.h"

#include "Renderer.h"
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Animation.h"

#include "LuaReader.h"

#include "vector"
#include "iostream"
#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
    try {

        //// Aquí empieza el test de la cámara
        //ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
        //ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cp3;

        //Entity* camera = new Entity();
        //camera->addComponent<Camera>();
        //camera->getComponent<Camera>()->setNearClipPlane(1);
        //camera->getComponent<Camera>()->setFarClipPlane(10000);
        //camera->getComponent<Camera>()->setAspectRatio(true);

        //camera->getComponent<Transform>()->setPosition(0, 0, 1000);
        //camera->getComponent<Transform>()->setRotation(0, 0, 0);

        //camera->getComponent<Camera>()->setBackgroundColor(1.0f, 0.5f, 0.3137f);
        ////Aquí acaba el test

        //Ogre::Light* luz = OgreMotor::GetInstance()->getSceneManager()->createLight("Luz");
        //luz->setType(Ogre::Light::LT_DIRECTIONAL);
        //luz->setDiffuseColour(0.0, 0.0, 0.0);

        //Ogre::SceneNode* lightNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("Luz");
        //lightNode->attachObject(luz);
        //lightNode->setDirection(Ogre::Vector3(0, -1, -1));

        //
       

        ////Aquí acaba el test
        //OgreMotor::GetInstance()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));

        ////Empieza el test del componente renderer
        //ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2;
        //ComponentFactoryRegistrations::ComponentFactoryRegistration<Animation> cpm3;
        //Entity* ent = new Entity();
        //ent->addComponent<Renderer>();
        //ent->addComponent<Animation>();
        //ent->getComponent<Transform>()->setScale({ 20,20,20 });
        //Animation* an = ent->getComponent<Animation>();
        //OgreMotor::GetInstance()->addInputListener(an);
        ////app.getRoot()->startRendering();
        //int i = 1;   
        //an->changeAnimation("Dance");

        //while (true) {
        //    camera->render();
        //    ent->render();
        //    Vector3<float> v = ent->getComponent<Transform>()->position();
        //    if (i % 250 == 0)
        //        an->changeAnimation(std::vector<std::string> { "RunBase", "RunTop" /*,"yht"*/ });
        //    else if (i % 200 == 0) {
        //        // an->changeAnimation("Dance");
        //        an->setLoop(false);
        //    }
        //    OgreMotor::GetInstance()->getRoot()->renderOneFrame();
        //    ++i;
        //}
        //delete ent;
        //delete camera;

        ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm("transform");
        ComponentFactoryRegistrations::ComponentFactoryRegistration<Renderer> cpm2("renderer");
        ComponentFactoryRegistrations::ComponentFactoryRegistration<Camera> cpm3("camera");
        OgreMotor::init("Motor de Ogre");

        readFile();

        while (true) {
            OgreMotor::GetInstance()->getRoot()->renderOneFrame();
        }
        OgreMotor::close();
    }
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
    }

    /*delete example;
    delete root;*/

    return 0;
}
