#include "BulletInstance.h"
#include "Transform.h"
#include "MotorLoop.h"

BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::BulletInstance() {
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_solver = new btSequentialImpulseConstraintSolver();
	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	_world->setGravity(DEFAULT_GRAVITY);
};

BulletInstance::~BulletInstance() {
	for (auto it : _collisionShapes) {
		delete it;
	}
	delete _world;
	delete _broadphase;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _solver;
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
}



