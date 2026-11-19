#include "melee_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

#include "health_component.h"

const unsigned int MeleeComponent::componentId;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void MeleeComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
}

void MeleeComponent::update(float dt)
{
	executeActiveAttack(dt);
}

void MeleeComponent::onRemove()
{

}

nlohmann::json MeleeComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void MeleeComponent::deserialize(nlohmann::json js)
{

}

void MeleeComponent::executeActiveAttack(float dt)
{
	if (!activeAttack)
	{
		return;
	}

	attackTimer += dt;

	float collisionCheckTime = activeAttack->attackDelay + activeAttack->attackCheckTime;
	float hangTime = collisionCheckTime + activeAttack->postAttackDelay;

	if (attackTimer > activeAttack->attackDelay && attackTimer < collisionCheckTime)
	{
		if (hitCheckDone)
		{
			return;
		}

		// Check collision
		glm::vec3 start = transform->getLocalPosition();
		float distance = activeAttack->distance;
		
		Contact hit;
		bool hitFound = FikaServers::getPhysicsSolver().getCollisionSolver().raycast(hit, start, attackDirection, distance, attackCollisionLayers);
		FikaServers::getMainRenderer().addLine(Line(start, start + attackDirection * distance, glm::vec3(0.9, 0.8, 0.4)));

		if (hitFound)
		{
			// Deal damage
			Entity* hitEntity = FikaServers::getPhysicsSolver().getBodyEntity(*hit.body);
			if (!hitEntity)
			{
				hitCheckDone = true;
				return;
			}

			HealthComponent* healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*hitEntity, HealthComponent::componentId));

			if (healthCmp)
			{
				healthCmp->dealDamage(activeAttack->damage);
			}
		}

		hitCheckDone = true;
	}
	else if (attackTimer > collisionCheckTime && attackTimer < hangTime)
	{
		// Wait for next attack
	}
	else if (attackTimer > hangTime)
	{
		// Done
		activeAttack = nullptr;
		hitCheckDone = false;
		attackTimer = 0.0f;
	}
}

void MeleeComponent::startAttack()
{
	if (activeAttack)
	{
		return;
	}

	// Start new attack
	activeAttack = &attack;
	attackTimer = 0.0f;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

MeleeComponentUpdater::MeleeComponentUpdater()
{
}

void MeleeComponentUpdater::init(size_t poolSize)
{
	MeleeComponentUpdater* updater = new MeleeComponentUpdater();
	updater->components.init("Melee Components", poolSize);
	updater->targetComponentId = MeleeComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void MeleeComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* MeleeComponentUpdater::addComponent()
{
	return components.allocate();
}

void MeleeComponentUpdater::removeComponent(ECSComponent& component)
{
	MeleeComponent* casted = static_cast<MeleeComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
