#include "ComponentFactory.h"

ComponentFactory& ComponentFactory::getInstance()
{
	static ComponentFactory instance;
	return instance;
}

Component* ComponentFactory::getComponent(size_t index)
{
	auto it = _mGenerators.find(index);
	if (it != _mGenerators.end())
	{
		return it->second();
	}
	return nullptr;
}

Component* ComponentFactory::getComponent(std::string name)
{
	return getComponent(_mCompNames[name]);
}

size_t ComponentFactory::getComponentIndex(std::string name)
{
	return _mCompNames[name];
}

bool ComponentFactory::registerGenerator(size_t index, std::string compName, const componentInstanceGenerator& instGenerator)
{
	return _mGenerators.insert(std::make_pair(index, instGenerator)).second && _mCompNames.insert(std::make_pair(compName, index)).second;
}