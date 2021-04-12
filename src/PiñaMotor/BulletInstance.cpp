#include "BulletInstance.h"
#include "MotorLoop.h"

BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::~BulletInstance()
{
	delete _world;
	delete _solver;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _broadphase;
}

BulletInstance* BulletInstance::getInstance() {
	if (_bulletInstance == nullptr) {
		_bulletInstance = new BulletInstance();
#ifdef _DEBUG
		std::cout << "Nueva instancia del bullet\n";
#endif
	}
#ifdef _DEBUG
	else std::cout << "Misma instancia del bullet\n";
#endif
	return _bulletInstance;
}

BulletInstance::BulletInstance(){
	// 1
	_broadphase = new btDbvtBroadphase();

	// 2
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);

	// 3
	_solver = new btSequentialImpulseConstraintSolver();

	// 4
	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);

	// 5
	_world->setGravity(btVector3(0, -9.8, 0));
};