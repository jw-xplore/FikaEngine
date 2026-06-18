#include "rigidBodyComponent.h"
#include "physics/physics.h"
#include "core/systemsHolder.h"
#include "core/gameobject.h"
#include "physics/collisions.h"
#include <iostream>

void RigidbodyComponent::start()
{
	PhysicsSolver* physics = SystemsHolder::getInstance()->getMainPhysicsSolver();
	transform = &owner->getTransform();
	body = &physics->addBody(*transform);

	// Callbacks
	body->onEnter = std::bind(&RigidbodyComponent::onEnter, this, std::placeholders::_1);

	// Test collider add
	CollisionSolver& collisions = physics->getCollisionSolver();
	Sphere* sphere = collisions.addCollider<Sphere>();
	sphere->body = body;
	sphere->radius = 2;

	collisions.addDebugMesh(*transform, sphere->radius);

	bodyFreezeMovement(*body, false, true, false);
}

void RigidbodyComponent::update(float dt)
{
	*transform = body->transform;
}

void RigidbodyComponent::setVelocity(glm::vec3 velocity) { body->velocity = velocity; }
void RigidbodyComponent::setBodyType(EBodyType type) { body->type = type; }
void RigidbodyComponent::setBodyTag(int tag) { body->tag = tag; }

void RigidbodyComponent::onEnter(Body& body)
{
	std::cout << "on enter: " << body.id << ", tag: " << body.tag << "\n";
}