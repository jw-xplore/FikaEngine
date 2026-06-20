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
	body->onExit = std::bind(&RigidbodyComponent::onExit, this, std::placeholders::_1);

	// Test collider add
	CollisionSolver& collisions = physics->getCollisionSolver();
	//collisions.addSphereCollider(*body, 0.5f);
	collisions.addBoxCollider(*body, glm::vec3(2, 1, 1));

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

void RigidbodyComponent::onExit(Body& body)
{
	std::cout << "on exit: " << body.id << ", tag: " << body.tag << "\n";
}