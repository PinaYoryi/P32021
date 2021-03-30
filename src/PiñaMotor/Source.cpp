#include <OgreRoot.h>
#include <btBulletDynamicsCommon.h>

#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
    Ogre::Root* root;
    root = new Ogre::Root();

    return 0;
}
