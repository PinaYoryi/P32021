#include "Renderer.h"
#include "OgreSceneManager.h"
#include "OgreMesh.h"
#include "OgreEntity.h"
#include "OgreMotor.h"
#include "Entity.h"
#include "Transform.h"
#include "Rigidbody.h"

Renderer::~Renderer()
{
	OgreMotor::GetInstance()->getSceneManager()->destroyEntity(_ogreEntity);
	OgreMotor::GetInstance()->getSceneManager()->destroySceneNode(_ogreNode);
}

bool Renderer::init(const std::map<std::string, std::string>& mapa){
	if (mapa.find("mesh") == mapa.end() || mapa.find("material") == mapa.end() || mapa.find("visible") == mapa.end()) return false;
	
	_ogreNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	Transform* tr = _myEntity->getComponent<Transform>();
	if ( tr == nullptr || !tr->isInitialized())
		return false;
	std::string me = mapa.at("mesh");
	setMesh(me);

	_ogreNode->attachObject(_ogreEntity);
	std::string ma = mapa.at("material");
	if(ma != "") setMaterial(ma);

	std::string vi = mapa.at("visible");
	if (vi == "true") setVisible(true);
	else if (vi == "false") setVisible(false);
	else return false;


	_ogreNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
	_ogreNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
	_ogreNode->setOrientation(tr->rotation());


	_initialized = true;

	return true;
}

void Renderer::setVisible(bool visible) {
	_visible = visible;
	_ogreNode->setVisible(visible);
}

bool Renderer::isVisible() {
	return _visible;
}

 void Renderer::setMaterial(std::string name) {
	_material = name;
	_ogreEntity->setMaterialName(name);
}

const std::string Renderer::getMaterialName() {
	return _material;
}

const std::string Renderer::getMeshName() {
	return _meshName;	
}

const Ogre::MeshPtr Renderer::getMesh() {
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode() const {
	return _ogreNode;
}

void Renderer::setMesh(std::string name) {
	_ogreEntity = _ogreNode->getCreator()->createEntity(name);
	_meshName = name;
}

void Renderer::setMesh(Ogre::MeshPtr mesh) {
	_ogreEntity = _ogreNode->getCreator()->createEntity(mesh);
}

void Renderer::render() {
	if (!_active || !_visible) return;
	
	if (_myEntity->hasComponent<Transform>()) {
		Transform* tr = _myEntity->getComponent<Transform>();
		_ogreNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_ogreNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_ogreNode->setOrientation(tr->rotation());
	}	
}




