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

	rb = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
	rb->getBody()->onEnterEvent.addListener([this](Body& body) { onBodyEnter(body); });
}

void EnemyComponent::update(float dt)
{
	glm::vec3 dir = playerTransform->getLocalPosition() - rb->getTransform()->getLocalPosition();
	glm::normalize(dir);

	rb->getBody()->velocity = dir * speed * dt;
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
