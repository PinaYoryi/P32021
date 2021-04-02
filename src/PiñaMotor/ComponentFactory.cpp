#include "ComponentFactory.h"
#include "ecs.h"

 ComponentFactory& ComponentFactory::getInstance()
 {
     static ComponentFactory instance;
     return instance;
 }

// template<typename T>
//T* ComponentFactory::getComponent()
// {    
//     auto it = _mGenerators.find(indexOf<T,ComponentsList>);
//     if (it != _mGenerators.end())
//     {
//         return it->second();
//     }
//	return nullptr;
// }
//template<typename T>
//bool ComponentFactory::registerGenerator( const componentInstanceGenerator& instGenerator)
//{
//	return _mGenerators.insert(std::make_pair(indexOf<T, ComponentsList>, instGenerator)).second;
//}