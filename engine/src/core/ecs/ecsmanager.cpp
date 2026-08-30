#include "ecsmanager.h"
#include "ecssystembase.h"
#include "ecscomponent.h"
#include "ecsentity.h"
#include <cassert>

namespace FikaECS
{
	void ECSManager::init()
	{
		systems.reserve(64);
	}

	void ECSManager::update(float dt)
	{
		for (auto& system : systems)
		{
			system->update(dt);
		}
	}

	Component* ECSManager::addComponent(Entity& entity, unsigned int componentId)
	{
		bool systemExist = componetIdSystems.find(componentId) != componetIdSystems.end();
		if (!systemExist)
		{
			std::cout << "Fail to add component. System for id: " << componentId << " was never registered \n";
			std::cout << "Add system into ECSManager \n";
			assert(false);
		}

		// Add component to system
		Component* comp = componetIdSystems[componentId]->addComponent();

		// Store relation
		entityComponets[entity.getId()].push_back(componentId);

		return comp;
	}

	void ECSManager::addComponentIdSystem(SystemBase* system)
	{
		unsigned int id = system->componentID();
		componetIdSystems[system->componentID()] = system;
		std::cout << "Added system id: " << id << "\n";
	}
}