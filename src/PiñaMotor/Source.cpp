#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include "BulletInstance.h"
#include "MotorLoop.h"

#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
    Ogre::Root* root;
    root = new Ogre::Root();
    delete root;
    //TODO: carne de ca�on de macro
 /*   ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    Entity* ent = new Entity();*/


    cout << "Primero" << endl;
    BulletInstance* bI = BulletInstance::getInstance();
    cout << "Segundo" << endl;
    bI = BulletInstance::getInstance();
    cout << "Tercero" << endl;
    BulletInstance::getInstance()->getWorld();
    
    if (bI != nullptr)
        delete bI;

    system("pause");

    return 0;
}
