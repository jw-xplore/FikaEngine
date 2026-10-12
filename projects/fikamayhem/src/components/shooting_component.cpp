#include "Shooting_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "../core/content_manager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void ShootingComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
}

void ShootingComponent::update(float dt)
{

}

void ShootingComponent::onRemove()
{

}

nlohmann::json ShootingComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void ShootingComponent::deserialize(nlohmann::json js)
{

}

void ShootingComponent::runTimers(float dt)
{
	// Reload
	if (reloadTimer > 0)
	{
		reloadTimer -= dt;
		return;
	}

	// Fire
	if (fireTimer > 0)
	{
		fireTimer -= dt;
		return;
	}
}

void ShootingComponent::fire(float angle)
{
	if (reloadTimer > 0 || fireTimer > 0)
	{
		return;
	}

	float angleChange = 0;

	if (bulletsPerFire > 1)
	{
		// Angles distribution
		int num = bulletsPerFire;
		if (cone < 360)
		{
			angle -= glm::radians(cone * 0.5f);
			num -= 1;
		}

		float split = cone / static_cast<float>(num);
		angleChange = glm::radians(split);
	}

	for (size_t i = 0; i < bulletsPerFire; i++)
	{
		// Velocity
		float ang = angle + i * angleChange;
		glm::vec3 vel = glm::vec3(sin(ang), 0, cos(ang));
		vel = glm::normalize(vel);
		vel *= bulletSpeed;

		ContentManager::createBullet(transform->getLocalPosition(), vel, 3, bulletLayer);
	}

	// Ammo and timer
	if (maxAmmo > 0)
	{
		ammo--;
	}

	fireTimer = fireDelay;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

ShootingComponentUpdater::ShootingComponentUpdater()
{
}

void ShootingComponentUpdater::init(size_t poolSize)
{
	ShootingComponentUpdater* updater = new ShootingComponentUpdater();
	updater->components.init("Shooting Components", poolSize);
	updater->targetComponentId = ShootingComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void ShootingComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* ShootingComponentUpdater::addComponent()
{
	return components.allocate();
}

void ShootingComponentUpdater::removeComponent(ECSComponent& component)
{
	ShootingComponent* casted = static_cast<ShootingComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
