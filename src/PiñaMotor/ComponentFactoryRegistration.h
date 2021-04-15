#pragma once
#include "ComponentFactory.h"
#include "ecs.h"
/// <summary>
/// clase para registrar los nuevos componentes
/// forma de uso:						donde Transform es el nombre del componente a añadir
/// ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
/// </summary>
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