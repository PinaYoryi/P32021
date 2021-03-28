#pragma once
#include "ComponentFactory.h"

namespace ComponentFactoryRegistrations {
	template<typename T> class ComponentFactoryRegistration {
	public:
		ComponentFactoryRegistration(const char* id) {
			ComponentFactory::get().registerGenerator(id, []()
				{
					return static_cast<Component*>(new T());
				}
			);
		}
	};
}