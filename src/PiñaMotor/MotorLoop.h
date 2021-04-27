#pragma once

#include "OgreMotor.h"
#include "Entity.h" //<------Esto es placeholder de la escena que crea SceneManager

//Unidad de tiempo tras la cual se actualizan las físicas.
const float FIXED_UPDATE_TIME = 0.02f;

class MotorLoop {
public:
	~MotorLoop();

	/// <summary>
	/// Devuelve una instancia de la clase. Devuelve nullptr por defecto si no se ha inicializado.
	/// Para inicializarla se usa Init().
    /// </summary>
	static MotorLoop* GetInstance();

	/// <summary>
	/// Inicializa la clase MotorLoop con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya hab�a sido inicializada.
	/// Todo: Implementar los parametros a inicializar.
	/// </summary>
	static bool Init();

	/// <summary>
	/// Inicializa el bucle principal Input -> FixedUpdate -> Update -> Render
	/// </summary>
	void startLoop();
	/// <summary>
	/// Lee los inputs que se den en el frame. Devuelve false en caso de error.
	/// </summary>
	void stopLoop();

protected:
	Entity* _ent; //<------Esto es placeholder de la escena que crea SceneManager
	Entity* _cam; //<------Esto es placeholder de la escena que crea SceneManager

	static MotorLoop* _singleton;

	bool _loop = false;
	int _lastTime = 0;
	float _accumulatedTime = 0;
	float _deltaTime = 0;

	//Lista de entidades

	MotorLoop() : _ent(nullptr), _cam(nullptr) {}; //<------Esto es placeholder de la escena que crea SceneManager

	/// <summary>
	/// Prepara la clase para inicializar el bucle principal del motor.
	/// </summary>
	void initLoop();
	/// <summary>
	/// Lee los inputs que se den en el frame. Devuelve false en caso de error.
	/// </summary>
	bool stepInput();
	/// <summary>
	/// Actualiza los componentes físicos. Devuelve false en caso de error.
	/// </summary>
	bool stepFixedUpdate();
	/// <summary>
	/// Actualiza los componentes lógicos. Devuelve false en caso de error.
	/// </summary>
	bool stepUpdate();
	/// <summary>
	/// Renderiza en pantalla lo componentes con esta propiedad. Devuelve false en caso de error.
	/// </summary>
	bool stepRender();
	/// <summary>
	/// Actualiza deltaTime y acumula el tiempo real transpirado para la ejecución de FixedUpdate
	/// </summary>
	void updateTime();


	void placeholderScene(); //<------Esto es placeholder de la escena que crea SceneManager



#pragma region Getters/Setters
public:
	/// <summary>
	/// Devuelve el deltaTime del último frame (el tiempo real que ha pasado entre frames).
	/// </summary>
	float getDeltaTime() { return _deltaTime; }
#pragma endregion
};