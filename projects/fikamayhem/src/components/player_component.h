#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>
#include "../components/health_component.h"
#include "../components/shooting_component.h"
#include <glm/gtc/quaternion.hpp>

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
	RigidBodyComponent* rb;
	HealthComponent* healthCmp;
	ShootingComponent* shootingCmp;
	float maxSpeed = 10;
	float currentSpeed = 0;
	float acceleration = 50;
	float decceleration = 100;
	glm::vec3 lastDirection = glm::vec3(1,0,0);

	Camera* camera;
	float cameraSpeed = 4.25f;
	float cameraTargetPrediction = 0.25f;
	const float cameraDistance = 5;
	const glm::vec3 camOffset = glm::vec3(-cameraDistance, cameraDistance, -cameraDistance);
	glm::vec3 lastCamPos = glm::vec3(0);

	bool isShooting = false;
	float bulletSpeed = 25;
	float fireDelay = 0.1f;
	float fireTimer = 0;

	float rotationSpeed = 15;
	float facing = 0;
	float facingTarget = 0;

	glm::quat rotCurrent = glm::quat(0, glm::vec3(0, 1, 0));
	glm::quat rotTarget = glm::quat(0, glm::vec3(0, 1, 0));

public:
	PlayerComponent() {}
	static const unsigned int componentId = 29311; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void movement(float dt);
	void rotate(float x, float y, float dt);
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
