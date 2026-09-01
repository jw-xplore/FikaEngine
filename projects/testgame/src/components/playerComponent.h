#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"
#include"fikaEngine.h"

struct Body;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief 
 */
class PlayerComponent : public FikaECS::ECSComponent
{
private:
	Body* body;
	float speed = 100;
	glm::vec3 lastDirection = glm::vec3(-1, 0, 0);

public:
	PlayerComponent() {}
	static const unsigned int componentId = 11740; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of PlayerComponent and run updates on them through ECS manager
 */
class PlayerComponentUpdater : public FikaECS::ComponentUpdater
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
	FikaECS::ECSComponent* addComponent() override;
};
