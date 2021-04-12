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
	//_ogreNode = OgreInstance::getInstance().getmSM()->getRootSceneNode()->createChildSceneNode("nombredel nodo");
	//_ogreEntity = _ogreEntity->createEntity(_mesh);
	// _ogreNode.attachedObject(_ogreEntity);
	//if(_material!="")
	//_ogreEntity.setMaterialName(_material)
	
	return true;
}
void Renderer::setVisible(bool visible){
	_visible = visible;
	//_ogreNode->setVisible(visible);
}

bool Renderer::isVisible(){
	return _visible;
}

void Renderer::setMaterial(std::string name){
	_material = name;
	//_ogreEntity->setMaterialName(name);
}

const std::string Renderer::getMaterialName(){
	return _material;
}
void Renderer::setMesh(std::string name)
{
	//_ogreEntity=_ogreNode->getCreator()->createEntity(name);
	_mesh = name;
}

void Renderer::setMesh(Ogre::MeshPtr mesh){
	_ogreEntity = _ogreNode->getCreator()->createEntity(mesh);
}

const std::string Renderer::getMeshName(){
	return _mesh;	
}

void Renderer::Render(){
	if (_visible) {
		if (_myEntity->hasComponent<Transform>()) {
			Transform* tr = _myEntity->getComponent<Transform>();
			_ogreNode->setPosition(tr->position().getX(), tr->position().getY(), tr->position().getZ());
			//_ogreNode->translate();
			_ogreNode->setScale(tr->scale().getX(), tr->scale().getY(), tr->scale().getZ());
			//Ogre::SceneNode* node = _myEntity->getComponent<Renderer>()->getNode();
			//node->setPosition(_position.getX(), _position.getY(), _position.getY());

			//_ogreNode->setOrientation(Ogre::Quaternion(Ogre::Degree(45), Vector3(1, 0, 0)));
		}
	}
}


const Ogre::MeshPtr Renderer::getMesh(){
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode() const{
	return _ogreNode;
}


