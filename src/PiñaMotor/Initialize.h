#pragma once

#include "OgreMotor.h"
#include "MotorLoop.h"
#include "Input.h"

class Initialize {
public:
	Initialize();
	~Initialize();

private:
	OgreMotor* _ogre;
	//BulletMotor _bullet;
	//FMODMotor _fmod;

	void startOgre();
	void stopOgre();

	void startBullet();
	void stopBullet();

	void startFMOD();
	void stopFMOD();
};