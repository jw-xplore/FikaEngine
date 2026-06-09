#include "rigidBodyComponent.h"
#include "physics/physics.h"
#include "core/systemsHolder.h"
#include "core/gameobject.h"

void RigidbodyComponent::start()
{
	body = &SystemsHolder::getInstance()->getMainPhysicsSolver()->addBody();
	transform = &owner->getTransform();
}

void RigidbodyComponent::update(float dt)
{
	*transform = body->transform;
}

void RigidbodyComponent::setVelocity(glm::vec3 velocity)
{
	body->velocity = velocity;
}