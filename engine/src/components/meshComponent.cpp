#include "MeshComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void MeshComponent::start()
{
	//instance = SystemsHolder::getInstance()->getMainRenderer()->addMeshInstance(&owner->getTransform(), meshRes, shader, texture);
}

void MeshComponent::update(float dt)
{

}


//-------------------------------------------------------
// System
//-------------------------------------------------------

MeshComponentUpdater::MeshComponentUpdater()
{
}

void MeshComponentUpdater::init()
{
	MeshComponentUpdater* updater = new MeshComponentUpdater();
	updater->components = new PoolAllocator<MeshComponent>("Mesh Components");
	updater->targetComponentId = MeshComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void MeshComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* MeshComponentUpdater::addComponent()
{
	return components->allocate();
}
