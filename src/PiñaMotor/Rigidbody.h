#pragma once

#include "Transform.h"
#include "Vector3.h"
#include <btBulletDynamicsCommon.h> 

const int DEFAULT_COLLISION_FLAGS = 1;
const float DEFAULT_MASS = 54.0f;
const float DEFAULT_RESTITUTION = 0.2f;

const float OGRE_BULLET_RATIO = 50; //TODO: Esto molaría no hacerlo

enum class ShapeTypes { Box, Sphere, Capsule };

class Rigidbody : public Component
{
public:

	Rigidbody() : _btRb(nullptr), _myMotionState(nullptr), _trans(nullptr) {}
	~Rigidbody();

	virtual bool init(const std::map<std::string, std::string>& mapa) override;
	virtual void update();


	void createShape(ShapeTypes type);

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
	void addForce(Vector3<float> force, Vector3<float> relativePos = { 0, 0, 0 });

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
	void setStatic(bool isStatic);

	// Define la velicidad
	void setLinearVelocity(Vector3<float> vector);

	// Actualiza el transform de bullet respecto a la clase Transform
	void updateTransform();

	// Modifica propiedades de la masa
	void setMass(float mass, const btVector3& inertia = { 0,0,0 });

private:
	btRigidBody* _btRb = nullptr;//es e rigidbody como tal
	btDefaultMotionState* _myMotionState = nullptr;//es el "transform" inicial de bullet 
	btCollisionShape* _btCs = nullptr;
	Transform* _trans = nullptr;
	bool _trigger = false;
	bool _kinematic = false;
	bool _static = false;
	bool _collision = false;
};
