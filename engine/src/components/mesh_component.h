#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include "renderer/resources/mesh_instance.h"

class Transform;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief Connects entity to renderer mesh instance
 */
class MeshComponent : public ECSComponent
{
private:
	MeshInstance* instance;
	Transform* transform;

public:
	MeshComponent() {}
	static const unsigned int componentId = 8974; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture);
	void setTexture(TextureResource& texture) { instance->setTexture(&texture); }
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of MeshComponent and run updates on them through ECS manager
 */
class MeshComponentUpdater : public ComponentUpdater
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
	ECSComponent* addComponent() override;
};
