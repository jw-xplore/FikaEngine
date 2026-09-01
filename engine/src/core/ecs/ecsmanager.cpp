#include "ecsmanager.h"
#include "ecscomponent.h"
#include "ecsentity.h"
#include <cassert>
#include "ecscomponentupdater.h"
#include "core/transform.h"
#include "components/transformComponent.h"
#include "components/rigidBodyComponent.h"

namespace FikaECS
{
	void ECSManager::init()
	{
		entities = new PoolAllocator<Entity>("entities");
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

		componentIdUpdaters[system->getTargetComponentId()] = system;

		return pos;
	}

	Entity* ECSManager::addEntity()
	{
		return entities->allocate();
	}

	ECSComponent* ECSManager::addComponent(Entity* entity, unsigned int componentId)
	{
		bool systemExist = componentIdUpdaters.find(componentId) != componentIdUpdaters.end();
		if (!systemExist)
		{
			std::cout << "Fail to add component. System for id: " << componentId << " was never registered \n";
			std::cout << "Add system into ECSManager \n";
			assert(false);
		}

		// Add component to system
		ComponentUpdater* updater = componentIdUpdaters[componentId];
		ECSComponent* comp = updater->addComponent();
		updater->storeOwner(entity, comp);
		
		comp->setOwnerEntity(entity);
		comp->start();

		// Store relation
		entityComponets[entity->getId()].push_back(componentId);

		return comp;
	}

	ECSComponent* ECSManager::findComponent(Entity& entity, unsigned int componentId)
	{
		return componentIdUpdaters[componentId]->getComponent(entity);
	}

	Transform* ECSManager::findEntityTransform(Entity& entity)
	{
		// Transform component
		ECSComponent* cmp = componentIdUpdaters[TransformComponent::componentId]->getComponent(entity);
		TransformComponent* transformCmp = static_cast<TransformComponent*>(cmp);
		if (transformCmp)
			return transformCmp->getTransform();

		// Rigidbody component
		cmp = componentIdUpdaters[RigidBodyComponent::componentId]->getComponent(entity);
		RigidBodyComponent* rbCmp = static_cast<RigidBodyComponent*>(cmp);
		if (rbCmp)
			return rbCmp->getTransform();
		
		return nullptr;
	}
}