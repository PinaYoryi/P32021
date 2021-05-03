#include "BulletInstance.h"
#include "Transform.h"
#include "MotorLoop.h"
BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::BulletInstance() {
	// Configuración de Bullet
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_solver = new btSequentialImpulseConstraintSolver();
	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	_world->setGravity(DEFAULT_GRAVITY);
}


BulletInstance::~BulletInstance() {
	if(_world) delete _world;
	if(_broadphase) delete _broadphase;
	if(_collisionConfiguration) delete _collisionConfiguration;
	if(_dispatcher) delete _dispatcher;
	if(_solver) delete _solver;
}

BulletInstance* BulletInstance::GetInstance() {
	return _bulletInstance;
}

bool BulletInstance::Init() {
	if (_bulletInstance != nullptr) return false;
	_bulletInstance = new BulletInstance(); return true;
}

void BulletInstance::update()
{
	_world->stepSimulation(FIXED_UPDATE_TIME);

	for (int i = 0; i < _dispatcher->getNumManifolds(); i++)
	{
		// Se consigue de la colision los dos rigidbodys
		btPersistentManifold* contactManifold = _dispatcher->getManifoldByIndexInternal(i);

		// Se cogen los datos del primer rigidbody
		const btCollisionObject* objectA = contactManifold->getBody0();
		const btRigidBody* rigidBodyA = btRigidBody::upcast(objectA);

		// Se cogen los datos del segundo rigidbody
		const btCollisionObject* objectB = contactManifold->getBody1();
		const btRigidBody* rigidBodyB = btRigidBody::upcast(objectB);

		// Cogemos nuestros Rigidbodys para decirle lo pertinente (si es la primera vez que colisiona o lleva mas veces)
		Rigidbody* rgA = static_cast<Rigidbody*>(rigidBodyA->getUserPointer());
		Rigidbody* rgB = static_cast<Rigidbody*>(rigidBodyB->getUserPointer());

		if (find(rgA)) {
			if (rgA->isTrigger()) {				
				rgA->onTriggerStay();
			}
			else {				
				rgA->onCollisionStay();
			}
		}
		else {
			if (rgA->isTrigger()) {
				rgA->onTriggerStart();
			}
			else {
				rgA->onCollisionStart();
			}
			_collisions.push_back(rgA);
		}
		if (find(rgB)) {
			if (rgB->isTrigger()) {
				rgB->onTriggerStay();
			}
			else {
				rgB->onCollisionStay();
			}
		}
		else {
			if (rgB->isTrigger()) {
				rgB->onTriggerStart();
			}
			else {
				rgB->onCollisionStart();
			}
			_collisions.push_back(rgB);

		}
	}
	endCollision();
}


bool BulletInstance::find(Rigidbody* rg)
{

	for (int i = 0; i < _collisions.size(); ++i) {
		if (rg == _collisions[i])
			return true;
	}
	return false;
}

void BulletInstance::endCollision()
{
	for (int j = 0; j < _collisions.size(); ++j) {
		bool find_ = false;
		for (int i = 0; i < _dispatcher->getNumManifolds() && !find_; i++)
		{
			// Se consigue de la colision los dos rigidbodys
			btPersistentManifold* contactManifold = _dispatcher->getManifoldByIndexInternal(i);

			// Se cogen los datos del primer rigidbody
			const btCollisionObject* objectA = contactManifold->getBody0();
			const btRigidBody* rigidBodyA = btRigidBody::upcast(objectA);

			// Se cogen los datos del segundo rigidbody
			const btCollisionObject* objectB = contactManifold->getBody1();
			const btRigidBody* rigidBodyB = btRigidBody::upcast(objectB);

			// Cogemos nuestros Rigidbodys para decirle lo pertinente 
			Rigidbody* rgA = static_cast<Rigidbody*>(rigidBodyA->getUserPointer());
			Rigidbody* rgB = static_cast<Rigidbody*>(rigidBodyB->getUserPointer());

			//si ya lo tenemos en nuestro vector de rigidbodys que han colisionado anteriormente dejamos de buscar 
			if (_collisions[j] == rgA || _collisions[j] == rgB)
				find_ = true;
		}
		//vemos si el rigidbody esta o no en las colisiones de este frame, si no lo esta se avisa que ha acabado la colision
		if (!find_) {
			if (_collisions[j]->isTrigger())
				_collisions[j]->onTriggerEnd();
			else
				_collisions[j]->onCollisionEnd();
			_collisions.erase(_collisions.begin() + j);
		}
				 
	}
}
