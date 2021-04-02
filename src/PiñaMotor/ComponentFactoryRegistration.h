#pragma once
#include "ComponentFactory.h"
#include "ecs.h"

namespace ComponentFactoryRegistrations {
	template<typename T> class ComponentFactoryRegistration {
	public:
		ComponentFactoryRegistration() {
			ComponentFactory::getInstance().registerGenerator(indexOf<T,ComponentsList>, []()
				{
					return static_cast<Component*>(new T());
				}
			);
		}
	};
}