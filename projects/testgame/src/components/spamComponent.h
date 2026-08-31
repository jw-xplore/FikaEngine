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
class SpamComponent : public FikaECS::ECSComponent
{
public:
	SpamComponent() {}
	static const unsigned int componentId = 17035; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of SpamComponent and run updates on them through ECS manager
 */
class SpamComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<SpamComponent>* components;

public:
	SpamComponentUpdater();

	/**
	 * @brief Call once at start to enable SpamComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};
