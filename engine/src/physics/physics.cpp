#include "physics.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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
	bodies = new PoolAllocator<Body>("Physics bodies", 256);

	tags.resize(8);
	tags[0] = DEFAULT_TAG;
}

PhysicsSolver::~PhysicsSolver()
{

}

void PhysicsSolver::update(float dt)
{
	for (size_t i = 0; i < bodies->getUsedAmount(); i++)
	{
		Body& body = (*bodies)[i];
		applyForce(body, body.velocity * dt);
	}

	// Collider calculations
	collisionsSolver.update(dt);
}

Body& PhysicsSolver::addBody(const glm::mat4& tranform)
{
	Body* body = bodies->allocate();
	int id = bodies->getUsedAmount();
	body->id = id;
	body->transform = tranform;

	// TODO: Make option to call this after all
	collisionsSolver.setupOngoinContacts(bodies->getUsedAmount());

	return (*bodies)[id - 1];
}

int PhysicsSolver::findTagId(std::string tag)
{
	for (size_t i = 0; i < tags.size(); i++)
	{
		if (tags[i] == tag)
			return i;
	}

	//std::cout << "Tag '" << tag << "' is not used";
	return -1;
}