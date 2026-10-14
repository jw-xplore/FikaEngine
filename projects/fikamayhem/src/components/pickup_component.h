#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>

using namespace FikaEngine;

enum EPickupType
{
	Health
};

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class PickupComponent : public ECSComponent
{
private:
	EPickupType type = EPickupType::Health;

public:
	PickupComponent() {}
	static const unsigned int componentId = 13663; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void setup(EPickupType type);
	void onBodyEnter(Body& body);
	void heal(Entity& entity);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of PickupComponent and run updates on them through ECS manager
 */
class PickupComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<PickupComponent> components;

public:
	PickupComponentUpdater();

	/**
	 * @brief Call once at start to enable PickupComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
