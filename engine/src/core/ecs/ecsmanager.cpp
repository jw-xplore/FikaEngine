#include "ecsmanager.h"
#include "ecscomponent.h"
#include "ecsentity.h"
#include <cassert>
#include "ecscomponentupdater.h"

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

	int ECSManager::registerSystem(ComponentUpdater* system)
	{
		int pos = systems.size();
		systems.push_back(system);

		componetIdSystems[system->getTargetComponentId()] = system;

		return pos;
	}

	ECSComponent* ECSManager::addComponent(Entity& entity, unsigned int componentId)
	{
		bool systemExist = componetIdSystems.find(componentId) != componetIdSystems.end();
		if (!systemExist)
		{
			std::cout << "Fail to add component. System for id: " << componentId << " was never registered \n";
			std::cout << "Add system into ECSManager \n";
			assert(false);
		}

		// Add component to system
		//ECSComponent* comp = componetIdSystems[componentId]->addComponent();
		componetIdSystems[componentId]->addComponent();

		// Store relation
		entityComponets[entity.getId()].push_back(componentId);

		return nullptr;
	}
}