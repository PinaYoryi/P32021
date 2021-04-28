#pragma once

class Initialize {
public:
	/// <summary>
	/// Inicia el motor. Arranca los motores adjuntos, carga la escena inicial y cede el control al loop principal.
	/// </summary>
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