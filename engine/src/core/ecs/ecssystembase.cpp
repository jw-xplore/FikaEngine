#include "ecssystembase.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecscomponent.h"
#include "core/systemsHolder.h"
#include <iostream>
#include <cassert>

namespace FikaECS
{
	SystemBase::SystemBase(unsigned int componentId)
	{
		/*
		if (componentId == 0)
			std::cout << "Component id 0 is invalid. Use component id to create matching system. \n";

		assert(componentId != 0);

		// Setup
		targetComponentId = componentId;

		components = std::make_unique<PoolAllocator<ECSComponent>>("ECS TestCmp", 256);
		*/
	}

	void SystemBase::update(float dt)
	{
		/*
		int size = components->getUsedAmount();

		for (size_t i = 0; i < size; i++)
		{
			(*components)[i].update(dt);
		}
		*/
	}

	ECSComponent* SystemBase::addComponent()
	{
		/*
		ECSComponent* cmp = components->allocate();
		cmp->start();

		return cmp;
		*/
		return nullptr;
	}
}