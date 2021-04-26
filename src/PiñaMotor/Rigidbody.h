#pragma once

#include "Component.h"
#include "Vector3.h"
#include "Transform.h"

#include <string>
#include <btBulletDynamicsCommon.h> 
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>


class Rigidbody : public Component
{
public:

	Rigidbody() {}
	~Rigidbody();

	virtual bool init(const std::map<std::string, std::string>& mapa) override;
	virtual void Update();

	// GETTERS
	// Devuelve si es un disparador
	inline bool isTrigger() const {
		return _trigger;
	}
	// Devuelve si es cinematico
	inline bool isKinematic() const {
		return _kinematic;
	}
	// Devuelve si es estatico
	inline bool isStatic() const {
		return _static;
	}

	// Devuelve la masa
	float getMass() {
		return _btRb->getMass();
	}

	// Devuelve la amortiguacion angular
	float getAngular() {
		return _btRb->getAngularDamping();
	}

	const btVector3 getForce() {
		return _btRb->getTotalForce();
	}

	// Devuelve la velicidad
	Vector3<float> getLinearVelocity();

	// SETTERS
	// Aplica la fuerza en la posicion relativa
	void addForce(Vector3<float> force, Vector3<float> relativePos);

	// Determina la friccion aplicada
	void setFriction(float friction) {
		_btRb->setFriction(friction);
	}

	// Coge la gravedad del body
	void setGravity(Vector3<float> gravity);

	// Define body como disparador
	void setTrigger(bool trigger);

	// Define si body sera cinematico
	void setKinematic(bool kinematic);

	// Define si body sera estatico
	void setStatic(bool static_);

	// Define la velicidad
	void setLinearVelocity(Vector3<float> vector);

	// Define impulso
	void setImpulse(const btVector3& impulse);

	// Modifica la posicion
	void setPosition(const Ogre::Vector3 newPos);

	// Modifica propiedades de la masa
	void setMass(float mass, const btVector3& inertia);

protected:

private:

	btRigidBody* _btRb = nullptr;
	Transform* _trans = nullptr;
	bool _trigger = false;
	bool _kinematic = false;
	bool _static = false;
	bool _collision = false;
};

