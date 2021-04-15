#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"

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
	ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
	//Entity* ent = new Entity();
	////ent->removeComponent<Transform>();
	//ent->getComponent<Transform>();

	Transform t1 = Transform();
	Transform t2 = Transform();

	//t2.setParent(&t1);

	//t1.rotate(120, 120, 30, Transform::Space::World);
	t2.rotate(10, 10, 0, Transform::Space::World);

	std::cout << "World " << t2.rotation().toEuler();
	std::cout << "Local " << t2.localRotation().toEuler() << "--------------------------------------------\n";

	t2.rotate(10, 10, 0, Transform::Space::World);

	std::cout << "World " << t2.rotation().toEuler();
	std::cout << "Local " << t2.localRotation().toEuler();


	delete root;
	return 0;
}
