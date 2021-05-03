#include "PinaMotor.h"

#if (defined _DEBUG)
#include <crtdbg.h>
int main() {
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

    PinaMotor* motor = new PinaMotor();
    motor->init("Motoraso");
    motor->launch("Archivo chulo de LUA");
    motor->close();
    delete motor;
    return 0;
}