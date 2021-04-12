#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
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


    // Bullet variables
    btBroadphaseInterface* _broadphase = nullptr;
    btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
    btCollisionDispatcher* _dispatcher = nullptr;
    btSequentialImpulseConstraintSolver* _solver = nullptr;
    btDiscreteDynamicsWorld* _world = nullptr;

    //initBullet();
    //1
    _broadphase = new btDbvtBroadphase();

    //2
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    //3
    _solver = new btSequentialImpulseConstraintSolver();

    //4
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);

    //5
    _world->setGravity(btVector3(0, -9.8, 0));

    //destroyBullet();
    delete _world;
    delete _solver;
    delete _collisionConfiguration;
    delete _dispatcher;
    delete _broadphase;

    return 0;
}
