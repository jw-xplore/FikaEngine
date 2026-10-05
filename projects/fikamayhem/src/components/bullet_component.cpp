#include "bullet_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void BulletComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
	transform->setScale(glm::vec3(1) * 0.2f);
}

void BulletComponent::update(float dt)
{
	transform->translate(velocity * dt);

	lifetime -= dt;
	if (lifetime <= 0)
	{

	}
}

nlohmann::json BulletComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void BulletComponent::deserialize(nlohmann::json js)
{

}

void BulletComponent::setup(glm::vec3 position, glm::vec3 velocity, float lifetime)
{
	transform->setPosition(position);
	this->velocity = velocity;
	this->lifetime = lifetime;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

BulletComponentUpdater::BulletComponentUpdater()
{
}

void BulletComponentUpdater::init(size_t poolSize)
{
	BulletComponentUpdater* updater = new BulletComponentUpdater();
	updater->components.init("Bullet Components", poolSize);
	updater->targetComponentId = BulletComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void BulletComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* BulletComponentUpdater::addComponent()
{
	return components.allocate();
}
