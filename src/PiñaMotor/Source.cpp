#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "MotorLoop.h"
#include "Input.h"

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
    //TODO: carne de canon de macro
    /*ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    Entity* ent = new Entity();*/

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Juegaso", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
    Input* example = Input::getInstance();
    while (!example->keyDown(SDL_SCANCODE_ESCAPE)) {
        example->update();
        if (example->keyDown(SDL_SCANCODE_SPACE)) cout << "Primer frame que se pulsa el espacio\n";
        if (example->keyHold(SDL_SCANCODE_SPACE)) cout << "Se sigue pulsando el espacio\n";
        if (example->keyUp(SDL_SCANCODE_SPACE)) cout << "Se ha dejado de pulsar el espacio\n";
        if (example->mouseDown(SDL_MOUSECODE_LEFT)) cout << "Primer frame que se hace click\n";
        if (example->mouseHold(SDL_MOUSECODE_LEFT)) cout << "Se sigue haciendo click\n";
        if (example->mouseUp(SDL_MOUSECODE_LEFT)) cout << "Se ha dejado de hacer click\n";
        if (example->wheelDir() == 1) cout << "La rueda se mueve hacia arriba\n";
        if (example->wheelDir() == -1) cout << "La rueda se mueve hacia abajo\n";
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete example;
    delete root;

    return 0;
}
