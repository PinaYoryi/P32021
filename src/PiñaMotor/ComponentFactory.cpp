#include "ComponentFactory.h"

bool ComponentFactory::registerGenerator(const char* typeName, const componentInstanceGenerator& instGenerator)
{
	return mGenerators.insert(std::make_pair(typeName, instGenerator)).second;
}