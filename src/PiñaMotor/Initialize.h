#pragma once

class Initialize {
public:
	Initialize();
	~Initialize();

private:
	void startOgre();
	void stopOgre();

	void startBullet();
	void stopBullet();

	void startFMOD();
	void stopFMOD();
};