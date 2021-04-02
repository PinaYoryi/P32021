#include "ComponentFactory.h"
#include "ecs.h"

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

bool ComponentFactory::registerGenerator(size_t index, const componentInstanceGenerator& instGenerator)
{
	return _mGenerators.insert(std::make_pair(index, instGenerator)).second;
}