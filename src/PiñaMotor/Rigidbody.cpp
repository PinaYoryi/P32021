#include "Rigidbody.h"
#include "BulletInstance.h"
#include "Entity.h"
#include "Renderer.h"
#include "OgreEntity.h"
Rigidbody::~Rigidbody() {
	if (_btCs) delete _btCs; _btCs = nullptr;
	if (_btRb) {
		BulletInstance::GetInstance()->getWorld()->removeRigidBody(_btRb);
		BulletInstance::GetInstance()->removeCollisionEntity(_myEntity);
		delete _btRb; _btRb = nullptr;
	}
	if(_myMotionState) delete _myMotionState; _myMotionState = nullptr;
}

bool Rigidbody::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("shape") == mapa.end() || mapa.find("mass") == mapa.end() || mapa.find("inertia") == mapa.end() || mapa.find("restitution") == mapa.end() ||
		mapa.find("damping") == mapa.end() || mapa.find("trigger") == mapa.end() || mapa.find("kinematic") == mapa.end()) return false;

	// Cogemos el puntero del componente Transform 
	_trans = _myEntity->getComponent<Transform>();
	if (_trans == nullptr) return false;

	// Vemos si es trigger o no
	bool trigger,kinematic;
	std::string s = mapa.at("trigger");
	if (s == "true") trigger = true;
	else if (s == "false") trigger = false;
	else return false;

	// leemos el Shape, -1 = no va a tener renderer
	s = mapa.at("shape");
	if (std::stof(s) >= 0 && ((_myEntity->getComponent<Renderer>() == nullptr && !trigger) || (_myEntity->getComponent<Renderer>()->getOgreEntity() == nullptr && !trigger)))
		return false;

	if (std::stof(s) == -1) createShape(ShapeTypes::Box, false);	// Si no debe tener
	else createShape((ShapeTypes)(std::stoi(s)));	// El tipo que debe tener

	s = mapa.at("kinematic");
	if (s == "true") kinematic = true;
	else if (s == "false") kinematic = false;
	else return false;

	// Creamos un Transform de Bullet a partir del componente Transform
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(_trans->position());
	startTransform.setRotation(_trans->rotation());
	_myMotionState = new btDefaultMotionState(startTransform);

	// Establecemos la masa
	s = mapa.at("mass");
	float _mass = std::stof(s);

	// Por defecto no tiene inercia
	s = mapa.at("inertia");
	std::string::size_type sz = 0, sa = 0;
	float a = std::stof(s, &sz);
	float b = std::stof(s.substr(sz + 1), &sa);
	float c = std::stof(s.substr(sz + sa + 2));
	btVector3 localInertia(a, b, c);
	_btCs->calculateLocalInertia(_mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(_mass, _myMotionState, _btCs, localInertia);

	// Lo creamos a partir de la informaci�n dada
	_btRb = new btRigidBody(rbInfo);	

	s = mapa.at("restitution");
	_btRb->setRestitution(std::stof(s));

	_btRb->setCollisionFlags(DEFAULT_COLLISION_FLAGS);

	s = mapa.at("damping");
	a = std::stof(s, &sz);
	b = std::stof(s.substr(sz + 1));
	_btRb->setDamping(a, b);

	_btRb->setMassProps(_mass, localInertia);

	_btRb->setUserPointer(_myEntity);

	setTrigger(trigger);
	setKinematic(kinematic);
	// Se a�ade al mundo de la simulaci�n f�sica
	BulletInstance::GetInstance()->getWorld()->addRigidBody(_btRb);
	setGravity(BulletInstance::GetInstance()->getGravity());

	return true;
}

void Rigidbody::fixedUpdate() {
	if (_trans != nullptr && _active && !_static)
		updateTransform();
}

void Rigidbody::updateTransform() {
	// Coge el transform del rigidbody tras la simulaci�n f�sica de este frame
	_btRb->setActivationState(ACTIVE_TAG);
	btTransform trans;
	_btRb->getMotionState()->getWorldTransform(trans);

	btQuaternion orientation = trans.getRotation();
	
	// Modifica el componente Transform del objeto
	_trans->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	_trans->setRotation(Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
}

void Rigidbody::createShape(ShapeTypes type, bool renderer) {
	if (renderer) {//si tiene renderer
		switch (type) {
		case ShapeTypes::Box: {//Box Shape, usa la escala del transform y utiliza parte de ogre
			Ogre::Vector3 half = _myEntity->getComponent<Renderer>()->getOgreEntity()->getBoundingBox().getHalfSize();
			half = Ogre::Vector3(_trans->scale().x * half.x, _trans->scale().y * half.y, _trans->scale().z * half.z);
			_btCs = new btBoxShape(btVector3(half.x, half.y, half.z));
		}
		break;
		case ShapeTypes::Sphere: {//Sphere Shape, usa la escala en x del transform y utiliza parte de ogre
			float half = _myEntity->getComponent<Renderer>()->getOgreEntity()->getBoundingBox().getHalfSize().x;
			half = _trans->scale().x * half;
			_btCs = new btSphereShape(half);
		}
		break;
		case ShapeTypes::Capsule: {//Capsule Shape, usa la escala en x e y del transform y utiliza parte de ogre
			Ogre::Vector3 half = _myEntity->getComponent<Renderer>()->getOgreEntity()->getBoundingBox().getHalfSize();
			half = Ogre::Vector3(_trans->scale().x * half.x, _trans->scale().y * half.y, _trans->scale().z * half.z);
			_btCs = new btCapsuleShape(half.x, half.y);
		}
		break;
		default:
			break;
		}
	}
	else {//si no tiene renderer, utiliza solo el transform y una constante que hace el shape sea del tamaño que queremos
		switch (type) {
		case ShapeTypes::Box:
				_btCs = new btBoxShape(_trans->scale() );
			break;
		case ShapeTypes::Sphere:
			_btCs = new btSphereShape(_trans->scale().x );
			break;
		case ShapeTypes::Capsule:
			_btCs = new btCapsuleShape(_trans->scale().x , _trans->scale().y);
			break;
		default:
			break;
		}
	}
}

void Rigidbody::addForce(Vector3<float> force, Vector3<float> relativePos) {

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
	_gravity = gravity;
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

void Rigidbody::setRotation(btQuaternion rotation)
{
	btTransform trans;
	_btRb->getMotionState()->getWorldTransform(trans);
	trans.setRotation(rotation);
	_btRb->setWorldTransform(trans);
	_btRb->getMotionState()->setWorldTransform(trans);
	
}

void Rigidbody::setPosition(Vector3<> pos)
{
	btTransform trans;
	_btRb->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(pos);
	_btRb->setWorldTransform(trans);
	_btRb->getMotionState()->setWorldTransform(trans);
}

void Rigidbody::setMass(float mass, const btVector3& inertia) {
	_btRb->setMassProps(mass, inertia);
}

