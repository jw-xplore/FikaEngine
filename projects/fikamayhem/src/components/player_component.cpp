#include "Player_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "../core/content_manager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void PlayerComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
	camera = FikaServers::getCameraManager().getMainCamera();
	camera->setPosition(transform->getLocalPosition() + camOffset);
	camera->lookAt(transform->getLocalPosition());
}

void PlayerComponent::update(float dt)
{
	// Movement
	InputManager& input = FikaServers::getInputManager();

	float vertical = 0;
	float horizontal = 0;

	if (input.isKeyHeld(Key::A))
	{
		horizontal += 1;
		vertical += -1;
	}
	if (input.isKeyHeld(Key::D))
	{
		horizontal += -1;
		vertical += 1;
	}

	if (input.isKeyHeld(Key::W))
	{
		horizontal += 1;
		vertical += 1;
	}
	if (input.isKeyHeld(Key::S))
	{
		horizontal += -1;
		vertical += -1;
	}

	if (horizontal > 1)
	{
		horizontal = 1;
	}
	else if (horizontal < -1)
	{
		horizontal = -1;
	}

	if (vertical > 1)
	{
		vertical = 1;
	}
	else if (vertical < -1)
	{
		vertical = -1;
	}

	glm::vec3 direction = glm::vec3(horizontal, 0, vertical);

	if (direction != glm::vec3(0))
	{
		glm::normalize(direction);
		lastDirection = direction;

		transform->translate(direction * speed * dt);
	}

	// Camera update
	camera->setPosition(transform->getLocalPosition() + camOffset);
	camera->lookAt(transform->getLocalPosition());

	// Fire
	handleFire(lastDirection, dt);
}

nlohmann::json PlayerComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void PlayerComponent::deserialize(nlohmann::json js)
{

}

void PlayerComponent::handleFire(glm::vec3 direction, float dt)
{
	if (fireTimer > 0)
	{
		fireTimer -= dt;
		return;
	}

	if (!FikaServers::getInputManager().isKeyHeld(Key::Space))
	{
		return;
	}

	// Fire
	ContentManager::createBullet(transform->getLocalPosition(), direction * bulletSpeed, 2);
	fireTimer = fireDelay;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

PlayerComponentUpdater::PlayerComponentUpdater()
{
}

void PlayerComponentUpdater::init(size_t poolSize)
{
	PlayerComponentUpdater* updater = new PlayerComponentUpdater();
	updater->components.init("Player Components", poolSize);
	updater->targetComponentId = PlayerComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void PlayerComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* PlayerComponentUpdater::addComponent()
{
	return components.allocate();
}

void PlayerComponentUpdater::removeComponent(ECSComponent& component)
{
	PlayerComponent* casted = static_cast<PlayerComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}