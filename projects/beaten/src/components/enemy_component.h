#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>

#include "melee_component.h"
#include "health_component.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class EnemyComponent : public ECSComponent
{
private:
	// Components
	RigidBodyComponent* rigidbodyCmp = nullptr;
	MeleeComponent* meleeCmp = nullptr;
	HealthComponent* healthCmp = nullptr;

public:
	EnemyComponent() {}
	static const unsigned int componentId = 23227; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void onDeath(Entity& entity);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of EnemyComponent and run updates on them through ECS manager
 */
class EnemyComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<EnemyComponent> components;

public:
	EnemyComponentUpdater();

	/**
	 * @brief Call once at start to enable EnemyComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
