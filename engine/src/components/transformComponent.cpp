#include "TransformComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

TransformComponent::TransformComponent(const glm::vec3& startPos)
{
	transform.setPosition(startPos);
}

void TransformComponent::start()
{

}

void TransformComponent::update(float dt)
{

}


//-------------------------------------------------------
// System
//-------------------------------------------------------

TransformComponentUpdater::TransformComponentUpdater()
{
}

void TransformComponentUpdater::init()
{
	TransformComponentUpdater* updater = new TransformComponentUpdater();
	updater->components = new PoolAllocator<TransformComponent>("Transform Components");
	updater->targetComponentId = TransformComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void TransformComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* TransformComponentUpdater::addComponent()
{
	return components->allocate();
}
