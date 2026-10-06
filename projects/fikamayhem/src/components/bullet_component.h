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
class BulletComponent : public ECSComponent
{
private:
	Transform* transform;
	glm::vec3 velocity = glm::vec3(0);
	float lifetime = 3;
	bool removed = false;

public:
	BulletComponent() {}
	static const unsigned int componentId = 19865; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void setup(glm::vec3 position, glm::vec3 velocity, float lifetime);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of BulletComponent and run updates on them through ECS manager
 */
class BulletComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<BulletComponent> components;

public:
	BulletComponentUpdater();

	/**
	 * @brief Call once at start to enable BulletComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
