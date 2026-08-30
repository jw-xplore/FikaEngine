#include "ecssystembase.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecscomponent.h"
#include "core/systemsHolder.h"

namespace FikaECS
{
	void SystemBase::update(float dt)
	{
		int size = components->getUsedAmount();

		for (size_t i = 0; i < size; i++)
		{
			(*components)[i].update(dt);
		}
	}

	Component* SystemBase::addComponent()
	{
		return components->allocate();
	}
}