#include "Renderer.h"
//#include "OgreMesh.h"
bool Renderer::init(const std::map<std::string, std::string>& mapa)
{
	//_ogreEntity = _myEntity.getOgreEntity();
	//_ogreNode = _myEntity.getOgreNode();
	return true;
}
void Renderer::setVisible(bool visible)
{
	_visible = visible;
	//_ogreNode->setVisible(visible);
}

bool Renderer::isVisible()
{
	return _visible;
}

void Renderer::setMaterial(std::string name)
{
	//_ogreEntity->setMaterialName(name);
	_material = name;
}

const std::string Renderer::getMaterialName()
{
	return _material;
}
void Renderer::setMesh(std::string name)
{
	//_ogreEntity=_ogreNode->getCreator()->createEntity(name);
	_mesh = name;
}

//void Renderer::setMesh(Ogre::MeshPtr mesh)
//{
//	_ogreEntity = _ogreNode->getCreator()->createEntity(mesh);
//}

const std::string Renderer::getMeshName()
{
	return _mesh;
}

void Renderer::Render()
{
	if (_visible) {

	}
}


//const Ogre::MeshPtr Renderer::getMesh()
//{
//	return _ogreEntity->getMesh();
//}
//

