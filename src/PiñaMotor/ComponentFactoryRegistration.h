#pragma once
#include "ComponentFactory.h"
#include "ecs.h"
/// <summary>
/// clase para registrar los nuevos componentes
/// forma de uso:						donde "transform" es el nombre del componente a añadir
/// ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform>("transform");
/// </summary>
namespace ComponentFactoryRegistrations {
	template<typename T> class ComponentFactoryRegistration {
	public:
		ComponentFactoryRegistration(std::string compName) {
			ComponentFactory::getInstance().registerGenerator(compName, []()
				{
					return static_cast<Component*>(new T());
				}
			);
		}
	};
}