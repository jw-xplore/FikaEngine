#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include"fika_engine.h"

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
	Body* body;
	RigidBodyComponent* rbCmp;
	float speed = 500;
	glm::vec3 lastDirection = glm::vec3(-1, 0, 0);
	glm::vec3 cameraOffset = glm::vec3(0, 6, -6);

public:
	PlayerComponent() {}
	static const unsigned int componentId = 11740; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;
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
	PoolAllocator<PlayerComponent>* components;

public:
	PlayerComponentUpdater();

	/**
	 * @brief Call once at start to enable PlayerComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	ECSComponent* addComponent() override;
};
