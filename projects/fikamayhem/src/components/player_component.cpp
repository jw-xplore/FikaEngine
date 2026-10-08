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

	healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*owner, HealthComponent::componentId));

	camera = FikaServers::getCameraManager().getMainCamera();
	camera->setPosition(transform->getLocalPosition() + camOffset);
	camera->lookAt(transform->getLocalPosition());
}

void PlayerComponent::update(float dt)
{
	// Movement
	movement(dt);

	// Camera update
	camera->setPosition(transform->getLocalPosition() + camOffset);
	camera->lookAt(transform->getLocalPosition());

	// Fire
	handleFire(dt);
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

void PlayerComponent::movement(float dt)
{
	glm::vec2 input = inputDirection(Key::D, Key::A, Key::W, Key::S);

	glm::vec3 direction = glm::vec3(input.x, 0, input.y);

	if (direction != glm::vec3(0))
	{
		direction = glm::normalize(direction);
		lastDirection = direction;

		transform->translate(direction * speed * dt);
	}
}

void PlayerComponent::handleFire(float dt)
{
	if (fireTimer > 0)
	{
		fireTimer -= dt;
		return;
	}

	glm::vec2 input = inputDirection(Key::Right, Key::Left, Key::Up, Key::Down);
	if (input == glm::vec2(0))
	{
		return;
	}

	// Fire
	glm::vec3 direction = glm::vec3(input.x, 0, input.y);
	ContentManager::createBullet(transform->getLocalPosition(), direction * bulletSpeed, 2);
	fireTimer = fireDelay;
}

glm::vec2 PlayerComponent::inputDirection(Key::Code right, Key::Code left, Key::Code up, Key::Code down)
{
	InputManager& input = FikaServers::getInputManager();

	float vertical = 0;
	float horizontal = 0;

	if (input.isKeyHeld(left))
	{
		horizontal += 1;
		vertical += -1;
	}
	if (input.isKeyHeld(right))
	{
		horizontal += -1;
		vertical += 1;
	}

	if (input.isKeyHeld(up))
	{
		horizontal += 1;
		vertical += 1;
	}
	if (input.isKeyHeld(down))
	{
		horizontal += -1;
		vertical += -1;
	}

	// No input
	if (horizontal == 0 && vertical == 0)
	{
		return glm::vec2(0);
	}

	// Cap and normalize
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

	glm::vec2 inputRes = glm::vec2(horizontal, vertical);
	inputRes = glm::normalize(inputRes);

	return inputRes;
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