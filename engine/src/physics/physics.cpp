#include "physics.h"
#include <glm/gtc/matrix_transform.hpp>

PhysicsSolver::PhysicsSolver()
{
	bodies.reserve(256);
}

PhysicsSolver::~PhysicsSolver()
{

}

void PhysicsSolver::update(float dt)
{
	// Apply physical forces 
	for (auto& body : bodies)
	{
		body->transform = glm::translate(body->transform, body->velocity * dt);
	}

	// Collider calculations
	collisionsSolver.update(dt);
}

Body& PhysicsSolver::addBody(const glm::mat4& tranform)
{
	std::unique_ptr<Body> body(new Body());
	body.get()->transform = tranform;
	bodies.push_back(std::move(body));

	return *bodies[bodies.size() - 1];
}