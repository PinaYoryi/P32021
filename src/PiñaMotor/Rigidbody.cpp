#include "Rigidbody.h"
#include "Entity.h"
#include "BulletInstance.h"
#include "Transform.h"

#include <btBulletDynamicsCommon.h> 
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>

Rigidbody::~Rigidbody() {
	delete _btRb; _btRb = nullptr;
	delete _myMotionState; _myMotionState = nullptr;
	//delete _trans; _trans = nullptr;
}

bool Rigidbody::init(const std::map<std::string, std::string>& mapa) {

	//quitar
	
	_trans = _myEntity->getComponent<Transform>();
	
	btCollisionShape* newRigidShape = new btBoxShape(5 * _trans->scale());
	//set the initial position and transform. For this demo, we set the tranform to be none
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(_trans->rotation());

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass;
	if (cont == 0)
		mass = 0.0f;//estatico
	else mass = 54.0f;
	btVector3 localInertia(0, 0, 0);

	startTransform.setOrigin(_trans->position());
	newRigidShape->calculateLocalInertia(mass, localInertia);

	//actually contruvc the body and add it to the dynamics world
	_myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, _myMotionState, newRigidShape, localInertia);
	_btRb = new btRigidBody(rbInfo);
	_btRb->setRestitution(0.2);
	_btRb->setCollisionFlags(1);
	//updateTransform();
	_btRb->setMassProps(mass, localInertia);

	_btRb->setUserPointer(_myEntity->getComponent<Transform>());
	
	BulletInstance::GetInstance()->getWorld()->addRigidBody(_btRb);
	BulletInstance::GetInstance()->addCollisionShape(newRigidShape);
	
	//quitar
	cont++;
	return true;
}


void Rigidbody::update() {
	if (_trans != nullptr && _active)
		updateTransform();
}

void Rigidbody::addForce(Vector3<float> force, Vector3<float> relativePos) {
	if (!_active)
		return;
	//para que si lleva un tiempo quieto, deje de estar dormido y reaccione a las fuerzas
	_btRb->setActivationState(ACTIVE_TAG);
	if (relativePos == Vector3<float>(0.0f, 0.0f, 0.0f))
		_btRb->applyCentralForce(force);
	else
		_btRb->applyForce(force, relativePos);
}

Vector3<float> Rigidbody::getLinearVelocity() {

	if (!_active) {
		throw "Cannot return linear velocity of disabled rigidbody";
	}
	const btVector3 v = _btRb->getLinearVelocity();

	return { v.x(), v.y(), v.z() };
}

void Rigidbody::setGravity(Vector3<float> gravity) {
	if (!_active)
		return;
	_btRb->setGravity(gravity);
}

void Rigidbody::setTrigger(bool trigger) {
	if (trigger)
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() |
			btCollisionObject::CF_NO_CONTACT_RESPONSE);
	else
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() &
			~btCollisionObject::CF_NO_CONTACT_RESPONSE);

	_trigger = trigger;
}

void Rigidbody::setKinematic(bool kinematic) {
	if (kinematic)
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() |
			btCollisionObject::CF_KINEMATIC_OBJECT);
	else
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() &
			~btCollisionObject::CF_KINEMATIC_OBJECT);
	_kinematic = kinematic;
}

void Rigidbody::setStatic(bool static_) {
	if (_static)
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() |
			btCollisionObject::CF_STATIC_OBJECT);
	else
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() &
			~btCollisionObject::CF_STATIC_OBJECT);
	_static = static_;
}

void Rigidbody::setLinearVelocity(Vector3<float> vector) {
	if (!_active)
		return;

	_btRb->setLinearVelocity(vector);
}

void Rigidbody::updateTransform() {
	btTransform initialTransform;
	initialTransform.setOrigin(_trans->position());
	initialTransform.setRotation(_trans->rotation());
	_btRb->setWorldTransform(initialTransform);
}

void Rigidbody::setMass(float mass, const btVector3& inertia ) {
	_btRb->setMassProps(mass, inertia);
}
