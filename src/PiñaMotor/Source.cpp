#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include "Vector2.h"

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
 /*   ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    Entity* ent = new Entity();*/

    Vector3<float> vec1 = Vector3<float>(1.0, 1.5, 2.0);
    Vector3<int> vec2 = Vector3<int>(5, 10, 15);
    vec1 *= 5; vec1.print();
    vec2 /= 2; vec2.print();
    cout << vec1.magnitude() << "\n";
    cout << vec2.magnitude() << "\n";
    vec1.normalized(); vec2.normalized();
    cout << vec1.getX() << " " << vec1.getY() << " " << vec1.getZ() << "\n";
    cout << vec2.getX() << " " << vec2.getY() << " " << vec2.getZ() << "\n";
    vec1 = Vector3<float>::forward(); vec1.print();
    vec2 = Vector3<int>::back(); vec2.print();

    Vector2<float> vec3 = Vector2<float>(1.0, 1.5);
    Vector2<int> vec4 = Vector2<int>(5, 10);
    vec3 *= 5; vec3.print();
    vec4 /= 2; vec4.print();
    cout << vec3.magnitude() << "\n";
    cout << vec4.magnitude() << "\n";
    vec3.normalized(); vec4.normalized();
    cout << vec3.getX() << " " << vec3.getY() << "\n";
    cout << vec4.getX() << " " << vec4.getY() << "\n";
    vec3 = Vector2<float>::up(); vec3.print();
    vec4 = Vector2<int>::down(); vec4.print();

    Ogre::Vector3 ogrevec = (Ogre::Vector3)Vector3<float>::forward();
    cout << ogrevec.x << " " << ogrevec.y << " " << ogrevec.z << "\n";

    delete root;
    return 0;
}
