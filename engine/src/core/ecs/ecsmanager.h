#pragma once
#include <vector>
#include <memory>
#include <map>
#include "core/memorymanagement.h"

class Transform;

namespace FikaECS
{
	//class SystemBase;
	class Entity;
	class ECSComponent;
	class ComponentUpdater;

	class ECSManager
	{
	private:
		PoolAllocator<Entity>* entities;
		std::vector<ComponentUpdater*> updaters;
		// Tracks which systems is used for component based on matching id
		std::map<unsigned int, ComponentUpdater*> componentIdUpdaters;
		// Entity-Component relation: entity id + component ids list
		std::map<unsigned int, std::vector<unsigned int>> entityComponets;

	public:
		ECSManager() {}
		~ECSManager() {}

		void init();
		void update(float dt);

		int registerUpdaters(ComponentUpdater* system);
		Entity* addEntity();
		ECSComponent* addComponent(Entity* entity, unsigned int componentId);
		ECSComponent* findComponent(Entity& entity, unsigned int componentId);
		Transform* findEntityTransform(Entity& entity);
	};
}