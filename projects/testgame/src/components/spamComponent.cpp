#include "SpamComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void SpamComponent::start()
{

}

void SpamComponent::update(float dt)
{

}


//-------------------------------------------------------
// System
//-------------------------------------------------------

SpamComponentUpdater::SpamComponentUpdater()
{
}

void SpamComponentUpdater::init()
{
	SpamComponentUpdater* updater = new SpamComponentUpdater();
	updater->components = new PoolAllocator<SpamComponent>("TestCmp");
	updater->targetComponentId = SpamComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void SpamComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* SpamComponentUpdater::addComponent()
{
	return components->allocate();
}
