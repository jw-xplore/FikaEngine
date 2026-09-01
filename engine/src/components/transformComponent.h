#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"
#include "core/transform.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief 
 */
class TransformComponent : public FikaECS::ECSComponent
{
private:
	Transform transform;

public:
	TransformComponent() {}
	static const unsigned int componentId = 2058; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;

	TransformComponent(const glm::vec3& startPos);
	Transform* getTransform() { return &transform; }
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of TransformComponent and run updates on them through ECS manager
 */
class TransformComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<TransformComponent>* components;

public:
	TransformComponentUpdater();

	/**
	 * @brief Call once at start to enable TransformComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};
