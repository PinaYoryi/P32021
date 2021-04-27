#include "BulletInstance.h"
#include "MotorLoop.h"
#include "OgreSceneNode.h"
#include "Transform.h"
BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::BulletInstance() {
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
	_world->setGravity(btVector3(0, -19.6, 0));

};

BulletInstance::~BulletInstance() {
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
	//if (this->physicsEngine != NULL) {
		_world->stepSimulation(1.0f / 60.0f); //suppose you have 60 frames per second
		//_world->getCo
		for (int i = 0; i < collisionShapes.size(); i++) {
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
					//sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
					tr->setRotation(Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));		
					//sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				}
			}
		}
	//}
	//return true;
}



