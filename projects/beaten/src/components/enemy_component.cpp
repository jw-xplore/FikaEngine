#include "enemy_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

const unsigned int EnemyComponent::componentId;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void EnemyComponent::start()
{
	// Setup components
	rigidbodyCmp = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
	//meleeCmp = static_cast<MeleeComponent*>(FikaServers::getECSManager().findComponent(*owner, MeleeComponent::componentId));
	healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*owner, HealthComponent::componentId));
	healthCmp->onDeath.addListener([this](Entity& entity) { onDeath(entity); });
}

void EnemyComponent::update(float dt)
{

}

void EnemyComponent::onRemove()
{

}

nlohmann::json EnemyComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void EnemyComponent::deserialize(nlohmann::json js)
{

}

void EnemyComponent::onDeath(Entity& entity)
{
	FikaServers::getECSManager().removeEntity(entity);
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

EnemyComponentUpdater::EnemyComponentUpdater()
{
}

void EnemyComponentUpdater::init(size_t poolSize)
{
	EnemyComponentUpdater* updater = new EnemyComponentUpdater();
	updater->components.init("Enemy Components", poolSize);
	updater->targetComponentId = EnemyComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void EnemyComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* EnemyComponentUpdater::addComponent()
{
	return components.allocate();
}

void EnemyComponentUpdater::removeComponent(ECSComponent& component)
{
	EnemyComponent* casted = static_cast<EnemyComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
