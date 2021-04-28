#include "BulletInstance.h"
#include "MotorLoop.h"
#include "OgreSceneNode.h"
#include "Transform.h"

BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::BulletInstance() {
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_solver = new btSequentialImpulseConstraintSolver();
	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	_world->setGravity(btVector3(0, -19.6, 0));
};

BulletInstance::~BulletInstance() {
	for (auto it : _collisionShapes) {
		delete it;
	}
	delete _world;
	delete _solver;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _broadphase;
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
	_world->stepSimulation(1.0f / 60.0f); //suppose you have 60 frames per second
	//_world->debugDrawWorld();//poner solo si queremos debugear el mundo de bullet, hay que hacer mas cosas aparte
	for (int i = 0; i < _collisionShapes.size(); i++) {
		btCollisionObject* obj = _world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);
			void* userPointer = body->getUserPointer();
			if (userPointer) {
				btQuaternion orientation = trans.getRotation();
				Transform* tr = static_cast<Transform*>(userPointer);
				tr->setPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
				tr->setRotation(Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));		
			}
		}
	}	
}



