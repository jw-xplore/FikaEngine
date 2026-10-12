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
	rb = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
	transform = FikaServers::getECSManager().findEntityTransform(*owner);

	healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(*owner, HealthComponent::componentId));
	healthCmp->onDeath.addListener([this](Entity& entity) { onDeath(entity); });
	healthCmp->onDamage.addListener([this](Entity& entity, int hp, int dmg) { onDamage(entity, hp, dmg); });

	shootingCmp = static_cast<ShootingComponent*>(FikaServers::getECSManager().findComponent(*owner, ShootingComponent::componentId));
	shootingCmp->bulletsPerFire = 1;
	shootingCmp->fireDelay = 0.25f;
	shootingCmp->setBulletLayer(2);
	shootingCmp->cone = 0;

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
	
	// Rotate
	rotCurrent = glm::slerp(rotCurrent, rotTarget, 1.0f);
	glm::vec3 rot = glm::vec3(0, rotCurrent.w * RAD_TO_DEG, 0);
	transform->setRotation(glm::vec3(0,rot.y,0));
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

		//transform->translate(direction * speed * dt);
		rb->getBody()->velocity = direction * speed * dt;

		if (!isShooting)
		{
			rotate(input.x, input.y, dt);
		}
	}
	else
	{
		rb->getBody()->velocity = glm::vec3(0);
	}
}

void PlayerComponent::rotate(float x, float y, float dt)
{
	float rot = atan2(x, y) * RAD_TO_DEG;

	if (rot < 0)
	{
		rot = rot + 360;
	}

	rotTarget.w = rot * DEG_TO_RAD;
}

void PlayerComponent::handleFire(float dt)
{
	shootingCmp->runTimers(dt);

	glm::vec2 input = inputDirection(Key::Right, Key::Left, Key::Up, Key::Down);
	if (input == glm::vec2(0))
	{
		isShooting = false;
		return;
	}

	glm::vec2 dir = glm::vec2(input.x, input.y);
	dir = glm::normalize(dir);
	float angle = atan2(dir.x, dir.y);

	shootingCmp->fire(angle);
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

void PlayerComponent::onDamage(Entity& entity, int hp, int dmg)
{
	glm::vec3 start = transform->getLocalPosition();
	glm::vec3 end = start + glm::vec3(0, 10, 0);
	FikaServers::getDebugRenderer().addLine(Line(start, end, glm::vec3(1, 0, 0)));
}

void PlayerComponent::onDeath(Entity& entity)
{
	FikaServers::getECSManager().removeEntity(entity);
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