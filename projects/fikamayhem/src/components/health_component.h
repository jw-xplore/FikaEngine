#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include "core/event.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class HealthComponent : public ECSComponent
{
private:
	int hp = 100;
	int maxHp = 100;

public:
	HealthComponent() {}
	static const unsigned int componentId = 32432; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	Event<void(Entity&, int, int)> onDamage;
	Event<void(Entity&)> onDeath;

	void dealDamage(int dmg);
	void heal(int amount);
	int getHp() { return hp; }
	int getMaxHp() { return maxHp; }
	bool isAlive() { return hp > 0; }
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of HealthComponent and run updates on them through ECS manager
 */
class HealthComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<HealthComponent> components;

public:
	HealthComponentUpdater();

	/**
	 * @brief Call once at start to enable HealthComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
