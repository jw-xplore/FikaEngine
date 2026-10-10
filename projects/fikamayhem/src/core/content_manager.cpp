#include "content_manager.h"
#include "../components/player_component.h"
#include "../components/bullet_component.h"
#include "../components/enemy_component.h"
#include "../components/health_component.h"
#include "../components/spawner_component.h"

Entity* ContentManager::playerEntity = nullptr;

ContentManager::ContentManager()
{
	playerEntity = nullptr;
}

ContentManager::~ContentManager()
{

}

void ContentManager::loadAssets()
{
	// TODO: Auto loading assets as part of engine core
	GPUResourceManager& gResourceManager = FikaServers::getGPUResourceManager();

	gResourceManager.loadMesh("assets/models/Player.obj", "player");
	gResourceManager.loadTexture("assets/textures/PlayerBaseCol.jpg", "player");
}

void ContentManager::buildPrefabs()
{
	// Fill list of prefabs
	std::vector<Entity> prefabs;
	prefabs.push_back(createPlayer());
	prefabs.push_back(createEnemy(glm::vec3(0)));
	prefabs.push_back(createBox(glm::vec3(0)));
	prefabs.push_back(createSpawner(glm::vec3(0), 3, 20, 2));

	// Generate prefabs
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GameResourceManager& gameres = FikaServers::getGameResourceManager();

	// TODO: Save data into source folder instead of binaries, Fix removing entities 
	for (Entity& prefab : prefabs)
	{
		std::string path = "assets/" + prefab.getName() + ".json";
		gameres.makePrefab(prefab, path.c_str());
		//ecsmngr.removeEntity(prefab);
	}
}

Entity& ContentManager::createPlayer()
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Player");

	RigidBodyComponent* rb = static_cast<RigidBodyComponent*>(ecsmngr.addComponent(entity, RigidBodyComponent::componentId));
	rb->setType(EBodyType::Kinematic);
	rb->setCapsuleCollider(0.5f, 1.0f);

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("player"), gpuRes.getShader("basic"), nullptr);
	// TODO: Fix texture loading
	mesh->setTexture(gpuRes.getTexture("player"));

	HealthComponent* health = static_cast<HealthComponent*>(ecsmngr.addComponent(entity, HealthComponent::componentId));

	PlayerComponent* player = static_cast<PlayerComponent*>(ecsmngr.addComponent(entity, PlayerComponent::componentId));

	playerEntity = entity;
	return *entity;
}

Entity& ContentManager::createBox(glm::vec3 position)
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Box");

	RigidBodyComponent* rb = static_cast<RigidBodyComponent*>(ecsmngr.addComponent(entity, RigidBodyComponent::componentId));
	rb->getTransform()->setLocalPosition(position);
	rb->setType(EBodyType::Static);
	rb->setBoxCollider(glm::vec3(1.0f));

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("cube"), gpuRes.getShader("basic"), nullptr);

	return *entity;
}

Entity& ContentManager::createBullet(glm::vec3 position, glm::vec3 velocity, float lifetime)
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Bullet");

	TransformComponent* tranCmp = static_cast<TransformComponent*>(ecsmngr.addComponent(entity, TransformComponent::componentId));

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("sphere"), gpuRes.getShader("basic"), nullptr);

	BulletComponent* bullet = static_cast<BulletComponent*>(ecsmngr.addComponent(entity, BulletComponent::componentId));
	bullet->setup(position, velocity, lifetime);

	return *entity;
}

Entity& ContentManager::createEnemy(glm::vec3 position)
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Enemy");

	RigidBodyComponent* rb = static_cast<RigidBodyComponent*>(ecsmngr.addComponent(entity, RigidBodyComponent::componentId));
	rb->getTransform()->setLocalPosition(position);
	rb->setType(EBodyType::Kinematic);
	rb->setSphereCollider(1.2f);
	rb->setInteractiveLayers(3);
	rb->setLayers(2);

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("sphere"), gpuRes.getShader("basic"), nullptr);

	HealthComponent* health = static_cast<HealthComponent*>(ecsmngr.addComponent(entity, HealthComponent::componentId));

	EnemyComponent* enemy = static_cast<EnemyComponent*>(ecsmngr.addComponent(entity, EnemyComponent::componentId));

	return *entity;
}

Entity& ContentManager::createSpawner(glm::vec3 position, float delay, int enemies, int enemiesPerSpawn)
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Spawner");

	TransformComponent* tranCmp = static_cast<TransformComponent*>(ecsmngr.addComponent(entity, TransformComponent::componentId));
	tranCmp->getTransform()->setPosition(position);

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("cube"), gpuRes.getShader("basic"), nullptr);

	SpawnerComponent* spawner = static_cast<SpawnerComponent*>(ecsmngr.addComponent(entity, SpawnerComponent::componentId));
	spawner->setup(delay, enemies, enemiesPerSpawn);

	return *entity;
}