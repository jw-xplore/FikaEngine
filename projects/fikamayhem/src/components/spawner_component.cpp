#include "Spawner_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "glm/gtc/random.hpp"
#include "../core/content_manager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void SpawnerComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
}

void SpawnerComponent::update(float dt)
{
	// Is empty?
	if (enemies <= 0)
	{
		return;
	}

	// Is player nearby?
	glm::vec3 playerPos = ContentManager::getPlayerTransform()->getLocalPosition();
	glm::vec3 dif = playerPos - transform->getLocalPosition();
	float dist = dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;

	if (dist > activateRange * activateRange)
	{
		// Deactivate if player is too far
		return;
	}

	// Run spawning
	runSpawner(dt);
}

void SpawnerComponent::onRemove()
{

}

nlohmann::json SpawnerComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void SpawnerComponent::deserialize(nlohmann::json js)
{

}

void SpawnerComponent::setup(float delay, int enemies, int enemiesPerSpawn)
{
	this->spawnDelay = delay;
	this->enemies = enemies;
	this->enemiesPerSpawn = enemiesPerSpawn;

	spawnTimer = delay;
}

void SpawnerComponent::runSpawner(float dt)
{
	if (spawnTimer > 0)
	{
		spawnTimer -= dt;
		return;
	}

	spawn();
	spawnTimer = spawnDelay;
}

void SpawnerComponent::spawn()
{
	for (size_t i = 0; i < enemiesPerSpawn; i++)
	{
		// Cancel if empty
		if (enemies <= 0)
		{
			break;
		}

		// Spawn at random position in range
		float x = glm::linearRand(-spawnRange, spawnRange);
		float z = glm::linearRand(-spawnRange, spawnRange);

		glm::vec3 pos = transform->getLocalPosition();
		ContentManager::createEnemy(pos + glm::vec3(x, 0, z));

		enemies--;
	}

	// Destroy when empty
	if (enemies <= 0)
	{
		FikaServers::getECSManager().removeEntity(*owner);
	}
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

SpawnerComponentUpdater::SpawnerComponentUpdater()
{
}

void SpawnerComponentUpdater::init(size_t poolSize)
{
	SpawnerComponentUpdater* updater = new SpawnerComponentUpdater();
	updater->components.init("Spawner Components", poolSize);
	updater->targetComponentId = SpawnerComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void SpawnerComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* SpawnerComponentUpdater::addComponent()
{
	return components.allocate();
}

void SpawnerComponentUpdater::removeComponent(ECSComponent& component)
{
	SpawnerComponent* casted = static_cast<SpawnerComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
