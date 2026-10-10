#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>
#include "../components/health_component.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
* @brief
*/
class PlayerComponent : public ECSComponent
{
private:
	Transform* transform;
	HealthComponent* healthCmp;
	float speed = 10;
	glm::vec3 lastDirection = glm::vec3(1,0,0);

	Camera* camera;
	const float cameraDistance = 5;
	glm::vec3 camOffset = glm::vec3(-cameraDistance, cameraDistance, -cameraDistance);

	bool isShooting = false;
	float bulletSpeed = 25;
	float fireDelay = 0.1f;
	float fireTimer = 0;

public:
	PlayerComponent() {}
	static const unsigned int componentId = 29311; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void movement(float dt);
	void handleFire(float dt);
	glm::vec2 inputDirection(Key::Code right, Key::Code left, Key::Code up, Key::Code down);
	void onDamage(Entity& entity, int hp, int dmg);
	void onDeath(Entity& entity);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of PlayerComponent and run updates on them through ECS manager
 */
class PlayerComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<PlayerComponent> components;

public:
	PlayerComponentUpdater();

	/**
	 * @brief Call once at start to enable PlayerComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
