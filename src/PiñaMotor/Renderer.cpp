#include "Renderer.h"
#include "OgreSceneManager.h"
#include "OgreMesh.h"
#include "OgreEntity.h"
#include "OgreInstance.h"
#include "Entity.h"
#include "Transform.h"
bool Renderer::init(const std::map<std::string, std::string>& mapa){
	//_mesh=map.mesh;
	//_material=map.material;
	//_ogreNode = OgreInstance::getInstance()->getmSM()->getRootSceneNode()->createChildSceneNode("nombredel nodo");
	//_ogreEntity = _ogreEntity->createEntity(_mesh);
	// _ogreNode.attachedObject(_ogreEntity);
	//if(_material!="")
	//_ogreEntity.setMaterialName(_material)
	_ogreEntity = OgreInstance::getInstance()->getmSM()->createEntity("Sinbad.mesh");
	_ogreNode = OgreInstance::getInstance()->getmSM()->getRootSceneNode()->createChildSceneNode("nSimbad");
	_ogreNode->attachObject(_ogreEntity);
	_ogreNode->setScale(20, 20, 20);
	_ogreNode->setPosition(20, 20, 20);
	return true;
}
void Renderer::setVisible(bool visible){
	_visible = visible;
	_ogreNode->setVisible(visible);
}

bool Renderer::isVisible(){
	return _visible;
}

 void Renderer::setMaterial(std::string name){
	_material = name;
	_ogreEntity->setMaterialName(name);
}

const std::string Renderer::getMaterialName(){
	return _material;
}


const std::string Renderer::getMeshName(){
	return _mesh;	
}


const Ogre::MeshPtr Renderer::getMesh() {
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode() const {
	return _ogreNode;
}


void Renderer::setMesh(std::string name)
{
	_ogreEntity = _ogreNode->getCreator()->createEntity(name);
	_mesh = name;
}

void Renderer::setMesh(Ogre::MeshPtr mesh) {
	_ogreEntity = _ogreNode->getCreator()->createEntity(mesh);
}


void Renderer::render(){
	if (_visible) {
		if (_myEntity->hasComponent<Transform>()) {
			Transform* tr = _myEntity->getComponent<Transform>();
			_ogreNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
			_ogreNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
			//TODO: Falta hacer la rotacion, es necesario usar Quaterniones
			//Vector3<float> rot = tr->rotation();
			_ogreNode->setOrientation(tr->rotation());
		}
	}
}




