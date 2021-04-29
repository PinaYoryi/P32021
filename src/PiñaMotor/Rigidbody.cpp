#include "Rigidbody.h"
#include "BulletInstance.h"
#include "Entity.h"

Rigidbody::~Rigidbody() {
	delete _btCs; _btCs = nullptr;
	delete _btRb; _btRb = nullptr;
	delete _myMotionState; _myMotionState = nullptr;
}

bool Rigidbody::init(const std::map<std::string, std::string>& mapa) {
	_trans = _myEntity->getComponent<Transform>();	
	_btCs = new btBoxShape(OGRE_BULLET_RATIO * _trans->scale());
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(_trans->rotation());

	btScalar mass = DEFAULT_MASS;
	btVector3 localInertia(0, 0, 0);

	startTransform.setOrigin(_trans->position());
	_btCs->calculateLocalInertia(mass, localInertia);

	_myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, _myMotionState, _btCs, localInertia);
	_btRb = new btRigidBody(rbInfo);
	_btRb->setRestitution(DEFAULT_RESTITUTION);
	_btRb->setCollisionFlags(DEFAULT_COLLISION_FLAGS);
	_btRb->setMassProps(mass, localInertia);
	
	BulletInstance::GetInstance()->getWorld()->addRigidBody(_btRb);

	return true;
}

void Rigidbody::update() {
	if (_trans != nullptr && _active)
		updateTransform();
}


void Rigidbody::createShape(ShapeTypes type)
{
	switch (type)
	{
	case ShapeTypes::Box:
		_btCs = new btBoxShape(_trans->scale());
		break;
	case ShapeTypes::Sphere:
		_btCs = new btSphereShape(_trans->scale().x);
		break;
	case ShapeTypes::Capsule:
		_btCs = new btCapsuleShape(_trans->scale().x, _trans->scale().y);
		break;
	default:
		break;
	}
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

void Rigidbody::setStatic(bool isStatic) {
	if (isStatic) {
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() |
			btCollisionObject::CF_STATIC_OBJECT);
		setMass(0.0f);
	}
	else {
		_btRb->setCollisionFlags(_btRb->getCollisionFlags() &
			~btCollisionObject::CF_STATIC_OBJECT);
		setMass(DEFAULT_MASS);
	}
	_static = isStatic;
}

void Rigidbody::setLinearVelocity(Vector3<float> vector) {
	if (!_active)
		return;

	_btRb->setLinearVelocity(vector);
}

void Rigidbody::updateTransform() {
	
	btTransform trans;
	_btRb->getMotionState()->getWorldTransform(trans);
			
	btQuaternion orientation = trans.getRotation();
	_trans->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	_trans->setRotation(Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			
}

void Rigidbody::setMass(float mass, const btVector3& inertia) {
	_btRb->setMassProps(mass, inertia);
}
