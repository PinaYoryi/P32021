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
};

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
}