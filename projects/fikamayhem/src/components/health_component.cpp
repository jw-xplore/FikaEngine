#include "Health_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void HealthComponent::start()
{
	hp = maxHp;
}

void HealthComponent::update(float dt)
{

}

void HealthComponent::onRemove()
{

}

nlohmann::json HealthComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void HealthComponent::deserialize(nlohmann::json js)
{

}

void HealthComponent::dealDamage(int dmg)
{
	hp -= dmg;
	onDamage.broadcast(*owner, hp, dmg);

	if (hp <= 0)
	{
		onDeath.broadcast(*owner);
	}
}

void HealthComponent::heal(int amount)
{
	hp += amount;
	if (hp > maxHp)
	{
		hp = maxHp;
	}
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

HealthComponentUpdater::HealthComponentUpdater()
{
}

void HealthComponentUpdater::init(size_t poolSize)
{
	HealthComponentUpdater* updater = new HealthComponentUpdater();
	updater->components.init("Health Components", poolSize);
	updater->targetComponentId = HealthComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void HealthComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* HealthComponentUpdater::addComponent()
{
	return components.allocate();
}

void HealthComponentUpdater::removeComponent(ECSComponent& component)
{
	HealthComponent* casted = static_cast<HealthComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
