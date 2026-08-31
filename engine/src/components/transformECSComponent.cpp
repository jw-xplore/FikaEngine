#include "TransformECSComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void TransformECSComponent::start()
{

}

void TransformECSComponent::update(float dt)
{

}


//-------------------------------------------------------
// System
//-------------------------------------------------------

TransformECSComponentUpdater::TransformECSComponentUpdater()
{
}

void TransformECSComponentUpdater::init()
{
	TransformECSComponentUpdater* updater = new TransformECSComponentUpdater();
	updater->components = new PoolAllocator<TransformECSComponent>("TransformECS Components");
	updater->targetComponentId = TransformECSComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void TransformECSComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* TransformECSComponentUpdater::addComponent()
{
	return components->allocate();
}
