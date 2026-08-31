#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"
#include "renderer/resources/meshInstance.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief Connects entity to renderer mesh instance
 */
class MeshComponent : public FikaECS::ECSComponent
{
private:
	MeshInstance* instance;

public:
	MeshComponent() {}
	static const unsigned int componentId = 8974; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of MeshComponent and run updates on them through ECS manager
 */
class MeshComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<MeshComponent>* components;

public:
	MeshComponentUpdater();

	/**
	 * @brief Call once at start to enable MeshComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};
