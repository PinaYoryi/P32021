#pragma once

#include <iostream> //TEMPORAL

//Unidad de tiempo tras la cual se actualizan las físicas.
const float UPDATE_TIME = 0.02;

class MotorLoop {
public:
	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static MotorLoop* getInstance();

	/// <summary>
	/// Inicializa el bucle principal Input -> FixedUpdate -> Update -> Render
	/// </summary>
	void startLoop();
	/// <summary>
	/// Lee los inputs que se den en el frame. Devuelve false en caso de error.
	/// </summary>
	void stopLoop();

	/// <summary>
	/// Añade una entidad a la lista de entidades del bucle principal. Devuelve true si logra hacerlo, false en caso contrario.
	/// </summary>
	bool addEntity();
	/// <summary>
	/// Retira una entidad de la lista de entidades del bucle principal. Devuelve true si logra hacerlo, false en caso contrario.
	/// </summary>
	bool removeEntity();

private:
	static MotorLoop* singleton_;

	bool loop_ = false;
	int lastTime_ = 0;
	float accumulatedTime_ = 0;
	float deltaTime_ = 0;

	//Lista de entidades

	MotorLoop() {};

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

	//Getters / Setters
public:
	/// <summary>
	/// Devuelve el deltaTime del último frame (el tiempo real que ha pasado entre frames).
	/// </summary>
	float getDeltaTime() { return deltaTime_; }
};