#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class SpawnerComponent : public ECSComponent
{
private:
	Transform* transform;
	float spawnTimer = 0;
	float spawnDelay = 3;

	float enemiesPerSpawn = 2;
	float enemies = 10;

	// In what distance from player will spawner be active
	float activateRange = 20; 

	float spawnRange = 10;

public:
	SpawnerComponent() {}
	static const unsigned int componentId = 21678; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void setup(float delay, int enemies, int enemiesPerSpawn);
	void runSpawner(float dt);
	void spawn();
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of SpawnerComponent and run updates on them through ECS manager
 */
class SpawnerComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<SpawnerComponent> components;

public:
	SpawnerComponentUpdater();

	/**
	 * @brief Call once at start to enable SpawnerComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
