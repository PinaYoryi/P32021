#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include "Vector2.h"
#include "UITransform.h"

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
    //TODO: carne de ca�on de macro
    ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm1;
    ComponentFactoryRegistrations::ComponentFactoryRegistration<UITransform> cpm2;

    Entity* obj1 = new Entity(); Entity* obj2 = new Entity();
    UITransform* ui1 = obj1->addComponent<UITransform>(); ui1->setHeight(500); ui1->setWidth(500); ui1->setAbsolutePos(Vector2<float>(50, 50));
    UITransform* ui2 = obj2->addComponent<UITransform>(); ui2->setHeight(100); ui2->setWidth(100); ui2->setParent(ui1); ui2->setAnchor(UITransform::middleAnchor()); ui2->setRelativePos(Vector2<float>(50, 50));
    Vector2<float> absPos1 = ui1->getAbsolutePos();
    Vector2<float> absPos2 = ui2->getAbsolutePos();
    absPos1.print(); //Posicion = 50, 50
    absPos2.print(); //Posicion = 50, 50 del padre + 500 * 0.5, 500 * 0.5 (panel del padre * anchor) + 50, 50 del hijo desde el anchor = 350, 350
    delete obj1;
    //delete obj2;
    delete root;
    return 0;
}
