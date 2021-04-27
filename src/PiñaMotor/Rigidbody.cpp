#include "Rigidbody.h"


Rigidbody::~Rigidbody() {
	delete _btRb; _btRb = nullptr;
	delete _trans; _trans = nullptr;
}

bool Rigidbody::init(const std::map<std::string, std::string>& mapa) {

	btScalar mass = 0.0f;
	btDefaultMotionState* ms = new btDefaultMotionState();
	//btCollisionShape* cs =

	/*auto search = mapa.find()
	if (search != mapa.end()) {
		std::cout << "Found " << search->first << " " << search->second << '\n';
	}
	else {
		std::cout << "Not found\n";
	}*/

	_btRb = new btRigidBody(mass, ms, nullptr);
	
	return true;
}

void Rigidbody::Update() {
	if (_trans != nullptr) {

		if (!_active)
			return;
		
		setPosition(_trans->position());
	}
}

void Rigidbody::addForce(Vector3<float> force, Vector3<float> relativePos) {
	if (!_active)
		return;

	if (relativePos == Vector3<float>(0.0f, 0.0f, 0.0f))
		_btRb->applyCentralForce((btVector3(
			btScalar(force.x), btScalar(force.y), btScalar(force.z))));
	else
		_btRb->applyForce(
			(btVector3(btScalar(force.x), btScalar(force.y),
				btScalar(force.z))),
			(btVector3(btScalar(relativePos.x), btScalar(relativePos.y),
				btScalar(relativePos.z))));
}

Vector3<float> Rigidbody::getLinearVelocity() {

	Vector3<float> linV(0.0f, 0.0f, 0.0f);
	if (!_active) {
		return linV;
	}
	const btVector3 v = _btRb->getLinearVelocity();
	linV.x = v.x(); linV.y = v.y(); linV.z = v.z();

	return linV;
}

void Rigidbody::setGravity(Vector3<float> gravity) {
	if (!_active)
		return;
	_btRb->setGravity(btVector3(btScalar(gravity.x), btScalar(gravity.x),
		btScalar(gravity.x)));
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

	_btRb->setLinearVelocity(btVector3(vector.x, vector.y, vector.z));
}

void Rigidbody::setPosition(const Ogre::Vector3 newPos) {
	if (!_active)
		return;
	btTransform initialTransform;
	initialTransform.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
	initialTransform.setRotation(_btRb->getOrientation());

	_btRb->setWorldTransform(initialTransform);
}

void Rigidbody::setMass(float mass, const btVector3& inertia) {
	_btRb->setMassProps(mass, inertia);
}

void Rigidbody::setImpulse(const btVector3& impulse) {
	_btRb->applyCentralImpulse(impulse);
}
