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
 /*   ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
	Entity* ent = new Entity();*/

	Vector3<float> vec1 = Vector3<float>(0.0, 0.0, 90);
	Vector3<float> vec2 = Vector3<float>(90, 0.0, 0.0);

	Quaternion a(Quaternion::euler(vec1));
	Quaternion b(Quaternion::euler(vec2));

	cout << "-------------------------------------------------------------------\n";
	vec1.print();
	cout << vec1.magnitude() << "\n";
	vec2.print();
	cout << vec2.magnitude() << "\n";

	cout << Quaternion::angle(a, b) * 180 / M_PI << "\n";

	vec1 = a.toEuler();
	vec2 = b.toEuler();

	vec1.print();
	vec2.print();
	cout << "-------------------------------------------------------------------\n";

	delete root;
	return 0;
}
