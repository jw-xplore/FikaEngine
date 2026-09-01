#include "MeshComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecsentity.h"
#include "core/transform.h"
#include "renderer/renderer.h"
#include <cassert>

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void MeshComponent::start()
{
	transform = SystemsHolder::getECSManager()->findEntityTransform(*owner);
	assert(transform);
}

void MeshComponent::update(float dt)
{

}

void MeshComponent::setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	instance = SystemsHolder::getInstance()->getMainRenderer()->addMeshInstance(&transform->getGlobalTransform(), meshRes, shader, texture);
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
