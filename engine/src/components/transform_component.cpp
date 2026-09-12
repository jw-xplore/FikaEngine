#include "transform_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"

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

	FikaServers::getECSManager().registerUpdaters(updater);
}

void TransformComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

ECSComponent* TransformComponentUpdater::addComponent()
{
	return components->allocate();
}
