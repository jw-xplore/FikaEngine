#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <string>
#include "components/transform_component.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class ShootingComponent : public ECSComponent
{
private:
	Transform* transform;
	int bulletLayer = 2;
	std::string bulletTargetTag = "enemy";

public:
	float cone = 360.0f;
	unsigned int bulletsPerFire = 1;
	float fireDelay = 0.1f;
	float fireTimer = 0.0f;
	float bulletSpeed = 20;

	unsigned int ammo = 0;
	unsigned int maxAmmo = 0;
	float reloadDelay = 0.0f;
	float reloadTimer = 0.0f;

	ShootingComponent() {}
	static const unsigned int componentId = 22164; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void runTimers(float dt);
	void fire(float angle);
	void setBulletLayer(int layer) { bulletLayer = layer; }
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of ShootingComponent and run updates on them through ECS manager
 */
class ShootingComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<ShootingComponent> components;

public:
	ShootingComponentUpdater();

	/**
	 * @brief Call once at start to enable ShootingComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
