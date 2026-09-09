#pragma once
#include <glm/glm.hpp>
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"

enum EBodyType;
struct Body;
class Transform;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief 
 */
class RigidBodyComponent : public FikaECS::ECSComponent
{
private:
	Body* body;

public:
	RigidBodyComponent() {}
	static const unsigned int componentId = 7099; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	Body* getBody() { return body; }
	Transform* getTransform();
	void setSphereCollider(float radius);
	void setBoxCollider(glm::vec3 volume);
	void setCapsuleCollider(float radius, float height);
	void setType(EBodyType type);
	void setLayers(unsigned int layers);
	void setInteractiveLayers(unsigned int layers);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of RigidBodyComponent and run updates on them through ECS manager
 */
class RigidBodyComponentUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<RigidBodyComponent>* components;

public:
	RigidBodyComponentUpdater();

	/**
	 * @brief Call once at start to enable RigidBodyComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};
