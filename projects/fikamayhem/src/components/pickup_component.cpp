#include "Pickup_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "../components/health_component.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void PickupComponent::start()
{
	RigidBodyComponent* rb = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
	rb->getBody()->onEnterEvent.addListener([this](Body& body) { onBodyEnter(body); });

	transform = FikaServers::getECSManager().findEntityTransform(*owner);
	startPosition = transform->getLocalPosition();
}

void PickupComponent::update(float dt)
{
	// Animation
	timer += dt * 4;
	float y = sin(timer) * 0.2f;
	float rot = timer * 5;

	transform->setLocalPosition(startPosition + glm::vec3(0,y,0));
	transform->setRotation(glm::vec3(0, rot, 0));
}

void PickupComponent::onRemove()
{

}

nlohmann::json PickupComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void PickupComponent::deserialize(nlohmann::json js)
{

}

void PickupComponent::setup(EPickupType type)
{
	this->type = type;
}

void PickupComponent::onBodyEnter(Body& body)
{
	Entity* entity = FikaServers::getPhysicsSolver().getBodyEntity(body);

	if (entity->getName() != "Player")
	{
		return;
	}

	switch (type)
	{
	case EPickupType::Health: heal(*entity); break;
	}

	FikaServers::getECSManager().removeEntity(*owner);
}

void PickupComponent::heal(Entity& entity)
{
	HealthComponent* healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(entity, HealthComponent::componentId));
	if (healthCmp->getHp() >= healthCmp->getMaxHp())
	{
		return;
	}
	
	healthCmp->heal(25);
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

PickupComponentUpdater::PickupComponentUpdater()
{
}

void PickupComponentUpdater::init(size_t poolSize)
{
	PickupComponentUpdater* updater = new PickupComponentUpdater();
	updater->components.init("Pickup Components", poolSize);
	updater->targetComponentId = PickupComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void PickupComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* PickupComponentUpdater::addComponent()
{
	return components.allocate();
}

void PickupComponentUpdater::removeComponent(ECSComponent& component)
{
	PickupComponent* casted = static_cast<PickupComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
