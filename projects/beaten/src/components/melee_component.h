#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include <fika_engine.h>

using namespace FikaEngine;

struct MeleeAttack
{
	int damage = 100;
	float distance = 2.0f;
	float attackDelay = 0.25f;
	float attackCheckTime = 0.1f; // Attack collision will be done in this window
	float postAttackDelay = 0.25f; // Wait after attack this long to chain next attack

	float getAttackTime() { return attackDelay + attackCheckTime; }
	float getTotalTime() { return attackDelay + attackCheckTime + postAttackDelay; }
};

enum EMeleeAttackState
{
	None = 0,
	Attacking = 1,
	Hitting = 2,
	Hanging = 3
};

//-------------------------------------------------------
// Component
//-------------------------------------------------------

/**
 * @brief
 */
class MeleeComponent : public ECSComponent
{
private:
	Transform* transform;

	EMeleeAttackState attackState = EMeleeAttackState::None;
	float attackTimer = 0.0f;
	bool hitCheckDone = false;
	glm::vec3 attackDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	int attackCollisionLayers = 1;

	int currentAttack = -1;
	std::vector<MeleeAttack> attacks;

	void executeActiveAttack(float dt);

public:
	MeleeComponent() {}
	static const unsigned int componentId = 31550; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
	void onRemove() override;
	nlohmann::json serialize() override;
	void deserialize(nlohmann::json js) override;

	void startAttack(int attackId);
	EMeleeAttackState getAttackState() { return attackState; }
	void setDirection(const glm::vec3& direction) { attackDirection = direction; }
	bool isAttacking() { return currentAttack > -1; }
	int getCurrentAttack() { return currentAttack; }
	int getNextAttack();
	std::vector<MeleeAttack>& getAttacks() { return attacks; }
};

//-------------------------------------------------------
// System
//-------------------------------------------------------

/**
 * @brief Holds pool of MeleeComponent and run updates on them through ECS manager
 */
class MeleeComponentUpdater : public ComponentUpdater
{
private:
	PoolAllocator<MeleeComponent> components;

public:
	MeleeComponentUpdater();

	/**
	 * @brief Call once at start to enable MeleeComponent pool update.
	 * Order of init call reflects in which order will updaters be processed.
	 */
	static void init(size_t poolSize);
	void update(float dt) override;
	ECSComponent* addComponent() override;
	void removeComponent(ECSComponent& component) override;
};
