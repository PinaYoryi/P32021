#include "MotorLoop.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	MotorLoop* loop = MotorLoop::getInstance();
	loop = MotorLoop::getInstance();
	loop->startLoop();
	delete loop;
	return 0;
}