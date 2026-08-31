#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief 
 */
class TransformECSComponent : public FikaECS::ECSComponent
{
private:

public:
	TransformECSComponent() {}
	static const unsigned int componentId = 7013; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of TransformECSComponent and run updates on them through ECS manager
 */
class TransformECSComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<TransformECSComponent>* components;

public:
	TransformECSComponentUpdater();

	/**
	 * @brief Call once at start to enable TransformECSComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};
