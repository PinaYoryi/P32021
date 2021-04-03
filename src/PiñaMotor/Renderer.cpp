#include "Renderer.h"

bool Renderer::init(const std::map<std::string, std::string>& mapa)
{
	//_ogreEntity = _myEntity.getOgreEntity();
	//_ogreNode = _myEntity.getOgreNode();
	return true;
}
void Renderer::setVisible(bool visible)
{
	_visible = visible;
	_ogreNode->setVisible(visible);
}

bool Renderer::isVisible()
{
	return _visible;
}

void Renderer::setMaterial(std::string name)
{
	_ogreEntity->setMaterialName(name);
}
