#pragma once
#include <vector>
#include <memory>
#include <map>
#include "ecssystembase.h"

namespace FikaECS
{
	//class SystemBase;
	class Entity;
	class ECSComponent;
	class ComponentUpdater;

	class ECSManager
	{
	private:
		std::vector<ComponentUpdater*> systems;
		// Tracks which systems is used for component based on matching id
		std::map<unsigned int, ComponentUpdater*> componetIdSystems;
		// Entity-Component relation: entity id + component ids list
		std::map<unsigned int, std::vector<unsigned int>> entityComponets;

		void addComponentIdSystem(SystemBase* system);

	public:
		ECSManager() {}
		~ECSManager() {}

		void init();
		void update(float dt);

		int registerSystem(ComponentUpdater* system);
		ECSComponent* addComponent(Entity& entity, unsigned int componentId);

		/*
		template <typename T>
		T* addSystem()
		{
			auto ptr = std::make_unique<T>();
			T* rawPtr = ptr.get();
			systems.push_back(std::move(ptr));

			// Store component-system relation
			SystemBase* system = dynamic_cast<SystemBase*>(rawPtr);
			addComponentIdSystem(system);

			return rawPtr;
		}
		*/
	};
}