#include "rigidBodyComponent.h"
#include "physics/physics.h"
#include "core/systemsHolder.h"
#include "core/gameobject.h"
#include "physics/collisions.h"

void RigidbodyComponent::start()
{
	PhysicsSolver* physics = SystemsHolder::getInstance()->getMainPhysicsSolver();
	transform = &owner->getTransform();
	body = &physics->addBody(*transform);

	// Test collider add
	CollisionSolver& collisions = physics->getCollisionSolver();
	Sphere* sphere = collisions.addCollider<Sphere>();
	sphere->body = body;
	sphere->radius = 2;
}

void RigidbodyComponent::update(float dt)
{
	*transform = body->transform;
}

void RigidbodyComponent::setVelocity(glm::vec3 velocity)
{
	body->velocity = velocity;
}

void RigidbodyComponent::setBodyType(EBodyType type)
{
	body->type = type;
}