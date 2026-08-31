#include "ecsmanager.h"
#include "ecscomponent.h"
#include "ecsentity.h"
#include <cassert>
#include "ecscomponentupdater.h"

namespace FikaECS
{
	void ECSManager::init()
	{
		updaters.reserve(64);
	}

	void ECSManager::update(float dt)
	{
		for (auto& system : updaters)
		{
			system->update(dt);
		}
	}

	int ECSManager::registerUpdaters(ComponentUpdater* system)
	{
		int pos = updaters.size();
		updaters.push_back(system);

		componetIdUpdaters[system->getTargetComponentId()] = system;

		return pos;
	}

	ECSComponent* ECSManager::addComponent(Entity& entity, unsigned int componentId)
	{
		bool systemExist = componetIdUpdaters.find(componentId) != componetIdUpdaters.end();
		if (!systemExist)
		{
			std::cout << "Fail to add component. System for id: " << componentId << " was never registered \n";
			std::cout << "Add system into ECSManager \n";
			assert(false);
		}

		// Add component to system
		//ECSComponent* comp = componetIdUpdaters[componentId]->addComponent();
		componetIdUpdaters[componentId]->addComponent();

		// Store relation
		entityComponets[entity.getId()].push_back(componentId);

		return nullptr;
	}
}