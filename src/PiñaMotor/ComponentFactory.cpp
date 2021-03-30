#include "ComponentFactory.h"

 ComponentFactory& ComponentFactory::getInstance()
 {
     static ComponentFactory instance;
     return instance;
 }

Component* ComponentFactory::getComponent(const char* typeName)
 {
     auto it = _mGenerators.find(typeName);
     if (it != _mGenerators.end())
     {
         return it->second();
     }
	return nullptr;
 }

bool ComponentFactory::registerGenerator(const char* typeName, const componentInstanceGenerator& instGenerator)
{
	return _mGenerators.insert(std::make_pair(typeName, instGenerator)).second;
}