#pragma once
#include <btBulletDynamicsCommon.h>
#include "Vector3.h"
#include <vector>
#include "Entity.h"

const Vector3<> DEFAULT_GRAVITY = { 0.0f, -9.8f, 0.0f };

class BulletInstance {
public:
	/// <summary>
	/// Destruye la instancia de la clase
	/// </summary>
	~BulletInstance();

	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static BulletInstance* GetInstance();

	/// <summary>
	/// Inicializa la clase BulletInstance con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya hab�a sido inicializada.
	/// Todo: Implementar los parametros a inicializar.
	/// </summary>
	static bool Init();

	// Getters
	inline btBroadphaseInterface* getBroadphase() const { return _broadphase; }
	inline btDefaultCollisionConfiguration* getCollisionConfiguration() const { return _collisionConfiguration; }
	inline btCollisionDispatcher* getDispatcher() const { return _dispatcher; }
	inline btSequentialImpulseConstraintSolver* getSolver() const { return _solver; }
	inline btDiscreteDynamicsWorld* getWorld() const { return _world; }

	// Setters
	inline void setBroadphase(btBroadphaseInterface* newBroadphase) { _broadphase = newBroadphase; }
	inline void setCollisionConfiguration(btDefaultCollisionConfiguration* newCollisionConfiguration) { _collisionConfiguration = newCollisionConfiguration; }
	inline void setDispatcher(btCollisionDispatcher* newDispatcher) { _dispatcher = newDispatcher; }
	inline void setSolver(btSequentialImpulseConstraintSolver* newSolver) { _solver = newSolver; }
	inline void setWorld(btDiscreteDynamicsWorld* newWorld) { _world = newWorld; }

	void removeCollisionEntity(Entity* ent);

	
	
	void update();
protected:
	/// <summary>
	/// Inicia los elementos del motor de físicas
	/// </summary>
	BulletInstance();

	static BulletInstance* _bulletInstance;

	void initResources();

private:
	// Atributos necesarios para el motor bullet
	btBroadphaseInterface* _broadphase = nullptr;
	btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
	btCollisionDispatcher* _dispatcher = nullptr;
	btSequentialImpulseConstraintSolver* _solver = nullptr;
	btDiscreteDynamicsWorld* _world = nullptr;

	//vector donde guardamos un pair con dos entidades, que representa una colision del frame anterior
	std::vector<std::pair<Entity*,Entity*>> _collisions;

	/// <summary>
	/// Analiza si en el vector "_collisions" si hay un pair con esas dos entidades
	/// tanto en ese orden (A-B) como en el inverso (B-A)
	/// </summary>
	bool find(Entity* entA,Entity* entB);

	/// <summary>
	/// Analiza si ha acabado una colision para avisar al TriggerEnd()/CollisionEnd()
	/// </summary>
	void endCollision();
};