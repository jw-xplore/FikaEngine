#include "Enemy_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "../core/content_manager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void EnemyComponent::start()
{
	Entity* player = ContentManager::getPlayerEntity();
	playerTransform = FikaServers::getECSManager().findEntityTransform(*player);

	transform = FikaServers::getECSManager().findEntityTransform(*owner);

	healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*owner, HealthComponent::componentId));

	rb = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
	rb->getBody()->onEnterEvent.addListener([this](Body& body) { onBodyEnter(body); });

	attackTimer = attackTimer;
}

void EnemyComponent::update(float dt)
{
	if (!healthCmp->isAlive())
	{
		FikaServers::getECSManager().removeEntity(*owner);
		return;
	}

	// Folow player
	glm::vec3 dir = playerTransform->getLocalPosition() - rb->getTransform()->getLocalPosition();
	dir = glm::normalize(dir);

	rb->getBody()->velocity = dir * speed * dt;

	// Attack
	attack(dt);
}

void EnemyComponent::onRemove()
{

}

nlohmann::json EnemyComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void EnemyComponent::deserialize(nlohmann::json js)
{

}

void EnemyComponent::onBodyEnter(Body& body)
{

}

void EnemyComponent::attack(float dt)
{
	glm::vec3 start = transform->getLocalPosition();
	glm::vec3 dir = playerTransform->getLocalPosition() - rb->getTransform()->getLocalPosition();
	dir = glm::normalize(dir);

	FikaServers::getDebugRenderer().addLine(Line(start, start + dir * attackLenght, glm::vec3(0, 1, 0)));

	// Timer
	if (attackTimer > 0)
	{
		attackTimer -= dt;
		return;
	}

	// Attack
	Contact* hit = FikaServers::getPhysicsSolver().getCollisionSolver().raycast(start, dir, attackLenght * 0.5f, rayLayer);

	if (hit)
	{
		// Attack player
		Entity* hitEntity = FikaServers::getPhysicsSolver().getBodyEntity(*hit->body);

		if (hitEntity == ContentManager::getPlayerEntity())
		{
			HealthComponent* healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*hitEntity, HealthComponent::componentId));
			healthCmp->dealDamage(attackDamage);
		}
	}

	attackTimer = attackDelay;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

EnemyComponentUpdater::EnemyComponentUpdater()
{
}

void EnemyComponentUpdater::init(size_t poolSize)
{
	EnemyComponentUpdater* updater = new EnemyComponentUpdater();
	updater->components.init("Enemy Components", poolSize);
	updater->targetComponentId = EnemyComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void EnemyComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* EnemyComponentUpdater::addComponent()
{
	return components.allocate();
}

void EnemyComponentUpdater::removeComponent(ECSComponent& component)
{
	EnemyComponent* casted = static_cast<EnemyComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
