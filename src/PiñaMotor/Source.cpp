#include "MotorLoop.h"

int main() {
	MotorLoop* loop = MotorLoop::getInstance();
	loop = MotorLoop::getInstance();
	loop->startLoop();
	return 0;
}