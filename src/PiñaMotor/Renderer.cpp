#include "Renderer.h"
#include "OgreSceneManager.h"
#include "OgreMesh.h"
#include "OgreEntity.h"

bool Renderer::init(const std::map<std::string, std::string>& mapa){
	//_mesh=map.mesh;
	//_material=map.material;
	//_ogreNode = mSM->getRootSceneNode()->createChildSceneNode("nombredel nodo");
	//_ogreEntity = mSM->getRootSceneNode()->createEntity(_mesh);
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

	}
}


const Ogre::MeshPtr Renderer::getMesh(){
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode(const std::string& name) const{
	return _ogreNode;
}


