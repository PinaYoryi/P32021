#include "Rigidbody.h"
#include "BulletInstance.h"
#include "Entity.h"

Rigidbody::~Rigidbody() {
	if (_btCs) delete _btCs; _btCs = nullptr;
	if (_btRb) delete _btRb; _btRb = nullptr;
	if(_myMotionState) delete _myMotionState; _myMotionState = nullptr;
}

bool Rigidbody::init(const std::map<std::string, std::string>& mapa) {
	// Cogemos el puntero del componente Transform 
	_trans = _myEntity->getComponent<Transform>();	

	// Creamos el Shape
	if(_myEntity->getName() == "sphere")
		createShape(ShapeTypes::Sphere);
	else
	createShape(ShapeTypes::Box);
	
	// Creamos un Transform de Bullet a partir del componente Transform
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(_trans->position());
	startTransform.setRotation(_trans->rotation());
	_myMotionState = new btDefaultMotionState(startTransform);

	// Establecemos la masa
	float _mass = DEFAULT_MASS;

	// Por defecto no tiene inercia
	btVector3 localInertia(0, 0, 0);
	_btCs->calculateLocalInertia(_mass, localInertia);

	// Creamos la configuracion del Rigidbody
	btRigidBody::btRigidBodyConstructionInfo rbInfo(_mass, _myMotionState, _btCs, localInertia);

	// Lo creamos a partir de la informaci�n dada
	_btRb = new btRigidBody(rbInfo);
	_btRb->setRestitution(1);
	_btRb->setCollisionFlags(DEFAULT_COLLISION_FLAGS);
	_btRb->setMassProps(_mass, localInertia);
	_btRb->setUserPointer(_myEntity);
	// Se a�ade al mundo de la simulaci�n f�sica
	BulletInstance::GetInstance()->getWorld()->addRigidBody(_btRb);

	return true;
}

void Rigidbody::update() {
	if (_trans != nullptr && _active)
		updateTransform();
}

void Rigidbody::updateTransform() {
	// Coge el transform del rigidbody tras la simulaci�n f�sica de este frame
	btTransform trans;
	_btRb->getMotionState()->getWorldTransform(trans);
	btQuaternion orientation = trans.getRotation();
	// Modifica el componente Transform del objeto
	_trans->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	_trans->setRotation(Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));	
}

void Rigidbody::createShape(ShapeTypes type)
{
	switch (type)
	{
	case ShapeTypes::Box:
		if(_myEntity->getName()!="Sinbad")
			_btCs = new btBoxShape(_trans->scale() * OGRE_BULLET_RATIO);
		else
			_btCs = new btBoxShape(_trans->scale() * 5);
		break;
	case ShapeTypes::Sphere:
		_btCs = new btSphereShape(_trans->scale().x * 100);
		break;
	case ShapeTypes::Capsule:
		_btCs = new btCapsuleShape(_trans->scale().x * OGRE_BULLET_RATIO, _trans->scale().y * OGRE_BULLET_RATIO);
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

void Rigidbody::setMass(float mass, const btVector3& inertia) {
	_btRb->setMassProps(mass, inertia);
}

