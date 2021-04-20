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

void Renderer::render(){
	if (_visible) {
		if (_myEntity->hasComponent<Transform>()) {
			Transform* tr = _myEntity->getComponent<Transform>();
			_ogreNode->setPosition(tr->position().getX(), tr->position().getY(), tr->position().getZ());
			_ogreNode->setScale(tr->scale().getX(), tr->scale().getY(), tr->scale().getZ());
			//TODO: Falta hacer la rotacion, es necesario usar Quaterniones
			//Vector3<float> rot = tr->rotation();
			//_ogreNode->setOrientation(Ogre::Quaternion(Ogre::Degree(rot.getX()), Vector3<float>(1, 0, 0)));
			//_ogreNode->setOrientation(Ogre::Quaternion(Ogre::Degree(rot.getX()), Vector3<float>(1, 0, 0)));
			//_ogreNode->setOrientation(Ogre::Quaternion(Ogre::Degree(rot.getX()), Vector3<float>(1, 0, 0)));
		}
	}
}


const Ogre::MeshPtr Renderer::getMesh(){
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode() const{
	return _ogreNode;
}


