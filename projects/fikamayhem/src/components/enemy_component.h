#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include "../components/player_component.h"
#include "../components/health_component.h"
#include "physics/physics.h"

using namespace FikaEngine;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class EnemyComponent : public ECSComponent
{
private:
	Transform* transform;
	Transform* playerTransform;
	HealthComponent* healthCmp;
	RigidBodyComponent* rb;

	int hp = 100;
	float speed = 1200;

	int attackDamage = 10;
	float attackDelay = 0.4;
	float attackTimer = 0;
	float attackLenght = 3;
	int rayLayer = 1;

public:
	EnemyComponent() {}
	static const unsigned int componentId = 26814; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void onBodyEnter(Body& body);
	void attack(float dt);
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of EnemyComponent and run updates on them through ECS manager
 */
class EnemyComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<EnemyComponent> components;
	
public:
	EnemyComponentUpdater();

	/**
	 * @brief Call once at start to enable EnemyComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
