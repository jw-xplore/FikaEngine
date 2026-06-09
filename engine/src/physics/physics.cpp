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
	for (auto& body : bodies)
	{
		body->transform = glm::translate(body->transform, body->velocity * dt);
	}
}

Body& PhysicsSolver::addBody()
{
	std::unique_ptr<Body> body(new Body());
	body.get()->transform = glm::mat4(1.0);
	bodies.push_back(std::move(body));

	return *bodies[bodies.size() - 1];
}