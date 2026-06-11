#include "physics.h"
#include <glm/gtc/matrix_transform.hpp>

void applyForce(Body& body, const glm::vec3& force)
{
	float x = force.x;
	float y = force.y;
	float z = force.z;

	// Ignore freezed axes
	EAxes xTest = (EAxes)(EAxes::X & body.freezeMovement);
	EAxes yTest = (EAxes)(EAxes::Y & body.freezeMovement);
	EAxes zTest = (EAxes)(EAxes::Z & body.freezeMovement);

	if (xTest == EAxes::X)
		x = 0;

	if (yTest == EAxes::Y)
		y = 0;

	if (zTest == EAxes::Z)
		z = 0;

	glm::vec3 newForce = glm::vec3(x, y, z);

	body.transform = glm::translate(body.transform, newForce);
}

void bodyFreezeMovement(Body& body, bool x, bool y, bool z)
{
	body.freezeMovement = (EAxes)0;

	if (x)
		body.freezeMovement = (EAxes)(body.freezeMovement | EAxes::X);
	if (y)
		body.freezeMovement = (EAxes)(body.freezeMovement | EAxes::Y);
	if (z)
		body.freezeMovement = (EAxes)(body.freezeMovement | EAxes::Z);
}

void bodyFreezeRotation(Body& body, bool x, bool y, bool z)
{
	body.freezeRotation = (EAxes)0;

	if (x)
		body.freezeRotation = (EAxes)(body.freezeRotation | EAxes::X);
	if (y)
		body.freezeRotation = (EAxes)(body.freezeRotation | EAxes::Y);
	if (z)
		body.freezeRotation = (EAxes)(body.freezeRotation | EAxes::Z);
}

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
		//body->transform = glm::translate(body->transform, body->velocity * dt);
		applyForce(*body, body->velocity * dt);
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