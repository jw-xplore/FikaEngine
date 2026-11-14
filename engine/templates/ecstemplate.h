#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class {{CLASS_NAME}}Component : public ECSComponent
{
private:

public:
	{{CLASS_NAME}}Component() {}
	static const unsigned int componentId = {{CMP_ID}}; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of {{CLASS_NAME}}Component and run updates on them through ECS manager
 */
class {{CLASS_NAME}}ComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<{{CLASS_NAME}}Component> components;

public:
	{{CLASS_NAME}}ComponentUpdater();

	/**
	 * @brief Call once at start to enable {{CLASS_NAME}}Component pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};