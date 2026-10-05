#include "content_manager.h"
#include "../components/player_component.h"
#include "../components/bullet_component.h"

ContentManager::ContentManager()
{

}

ContentManager::~ContentManager()
{

}

void ContentManager::init()
{

}

Entity& ContentManager::createPlayer()
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Player");

	RigidBodyComponent* rb = static_cast<RigidBodyComponent*>(ecsmngr.addComponent(entity, RigidBodyComponent::componentId));
	rb->setType(EBodyType::Kinematic);

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("cube"), gpuRes.getShader("basic"), nullptr);

	PlayerComponent* player = static_cast<PlayerComponent*>(ecsmngr.addComponent(entity, PlayerComponent::componentId));

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

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("cube"), gpuRes.getShader("basic"), nullptr);

	return *entity;
}

Entity& ContentManager::createBullet(glm::vec3 position, glm::vec3 velocity)
{
	ECSManager& ecsmngr = FikaServers::getECSManager();
	GPUResourceManager& gpuRes = FikaServers::getGPUResourceManager();

	Entity* entity = ecsmngr.addEntity("Bullet");

	TransformComponent* tranCmp = static_cast<TransformComponent*>(ecsmngr.addComponent(entity, RigidBodyComponent::componentId));

	MeshComponent* mesh = static_cast<MeshComponent*>(ecsmngr.addComponent(entity, MeshComponent::componentId));
	mesh->setup(gpuRes.getMesh("sphere"), gpuRes.getShader("basic"), nullptr);

	BulletComponent* bullet = static_cast<BulletComponent*>(ecsmngr.addComponent(entity, BulletComponent::componentId));
	bullet->setup(position, velocity, 3);

	return *entity;
}