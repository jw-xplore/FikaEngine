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
class {{NAME}}Component : public FikaECS::ECSComponent
{
public:
	{{NAME}}Component() {}
	static const unsigned int componentId = {{CMP_ID}}; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of {{NAME}}Component and run updates on them through ECS manager
 */
class {{NAME}}ComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<{{NAME}}Component>* components;

public:
	{{NAME}}ComponentUpdater();

	/**
	 * @brief Call once at start to enable {{NAME}}Component pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	void addComponent() override;
};