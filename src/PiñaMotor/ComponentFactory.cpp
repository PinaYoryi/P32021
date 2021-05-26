#include "ComponentFactory.h"

ComponentFactory& ComponentFactory::getInstance()
{
	static ComponentFactory instance;
	return instance;
}

Component* ComponentFactory::getComponent(std::string name)
{
	auto it = _mGenerators.find(name);
	if (it != _mGenerators.end())
	{
		return it->second();
	}
	return nullptr;
}

bool ComponentFactory::registerGenerator(std::string compName, const componentInstanceGenerator& instGenerator)
{
	return _mGenerators.insert(std::make_pair(compName, instGenerator)).second; 
}