#include "BulletInstance.h"
#include "Transform.h"
#include "MotorLoop.h"
#include "Entity.h"
#include "Rigidbody.h"
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
		Entity* entA =static_cast<Entity*>(rigidBodyA->getUserPointer());
		Entity* entB = static_cast<Entity*>(rigidBodyB->getUserPointer());

		if (find(entA)) {
			if (entA->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onTriggerStay();
			}
			else {				
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onCollisionStay();
			}
		}
		else {
			if (entA->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onTriggerStart();
			}
			else {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onCollisionStart();
			}
			_collisions.push_back(entA);
		}
		if (find(entB)) {
			if (entB->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onTriggerStay();
			}
			else {
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onCollisionStay();
			}
		}
		else {
			if (entB->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onTriggerStart();
			}
			else {
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onCollisionStart();
			}
			_collisions.push_back(entB);
		}
	}
	endCollision();
}


bool BulletInstance::find(Entity* rg)
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
			Entity* entA = static_cast<Entity*>(rigidBodyA->getUserPointer());
			Entity* entB = static_cast<Entity*>(rigidBodyB->getUserPointer());

			//si ya lo tenemos en nuestro vector de rigidbodys que han colisionado anteriormente dejamos de buscar 
			if (_collisions[j] == entA || _collisions[j] == entB)
				find_ = true;
		}
		//vemos si el rigidbody esta o no en las colisiones de este frame, si no lo esta se avisa que ha acabado la colision
		if (!find_) {
			if (_collisions[j]->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = _collisions[j]->getComponents()->begin(); comp != _collisions[j]->getComponents()->end(); comp++)
					comp->get()->onTriggerEnd();
			}
			else {
				for (auto comp = _collisions[j]->getComponents()->begin(); comp != _collisions[j]->getComponents()->end(); comp++)
					comp->get()->onCollisionEnd();
			}
			_collisions.erase(_collisions.begin() + j);
		}
				 
	}
}
