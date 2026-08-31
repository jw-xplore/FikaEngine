#pragma once
#include <vector>
#include <memory>
#include <map>

namespace FikaECS
{
	//class SystemBase;
	class Entity;
	class ECSComponent;
	class ComponentUpdater;

	class ECSManager
	{
	private:
		std::vector<ComponentUpdater*> updaters;
		// Tracks which systems is used for component based on matching id
		std::map<unsigned int, ComponentUpdater*> componetIdUpdaters;
		// Entity-Component relation: entity id + component ids list
		std::map<unsigned int, std::vector<unsigned int>> entityComponets;

	public:
		ECSManager() {}
		~ECSManager() {}

		void init();
		void update(float dt);

		int registerUpdaters(ComponentUpdater* system);
		ECSComponent* addComponent(Entity& entity, unsigned int componentId);
	};
}