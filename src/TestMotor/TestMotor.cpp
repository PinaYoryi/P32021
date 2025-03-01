// TestMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <PinaMotor.h>

#if (defined _DEBUG)
#include <crtdbg.h>
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
   // _CrtSetBreakAlloc(792654);
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
    PinaMotor motor;
    if (!motor.init("Test")) {
#if (defined _DEBUG)
        std::cerr << "\nError en init\n";
#endif
        motor.close();
        return -1;
    }

    if (!motor.launch("text.lua")) {
#if (defined _DEBUG)
        std::cerr << "\nError en launch\n";
#endif
        motor.close();
        return -1;
    }

    motor.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
