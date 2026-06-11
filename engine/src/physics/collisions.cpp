#include "collisions.h"
#include "physics.h"
#include "components/transform.h"
#include <glm/gtc/matrix_transform.hpp>

bool overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out)
{
	/*
	Vec3 d = posA - posB;
	float dist2 = dot(d, d);
	float rsum = A.radius + B.radius;
	float rsum2 = rsum * rsum;
	if (dist2 >= rsum2) return false;
	float dist = std::sqrt(dist2);
	float penetration = rsum - dist;
	Vec3 normal = dist > 1e-6f ? d / dist : Vec3(0, 1, 0);
	if (out) {
		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (B.radius - penetration * 0.5f); // approx contact on B
	}
	return true;
	*/

	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	glm::vec3 d = posA - posB;
	float dist2 = glm::dot(d, d);
	float rsum = colA.radius + colB.radius;
	float rsum2 = rsum * rsum;

	if (dist2 >= rsum)
		return false;

	float dist = std::sqrtf(dist2);
	float penetration = rsum - dist;
	glm::vec3 normal = dist > 1e-6f ? d / dist : glm::vec3(0, 1, 0);

	if (out)
	{
		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (colB.radius - penetration * 0.5f); // approx contact on B
	}

	return true;
}

void resolveSphereCollision(Sphere& colA, Sphere& colB, Contact& contact, float dt)
{
	Body& bodyA = *colA.body;
	Body& bodyB = *colB.body;

	glm::vec3 reaction = contact.normal * contact.penetration * PENETRATION_MULT;

	if (bodyA.type == EBodyType::Kinematic && bodyB.type == EBodyType::Static)
	{
		// First kinematic
		applyForce(bodyA, reaction);
	}
	else if (bodyA.type == EBodyType::Static && bodyB.type == EBodyType::Kinematic)
	{
		// Second kinematic
		applyForce(bodyB, -reaction);
	}
	else if (bodyA.type == EBodyType::Kinematic && bodyB.type == EBodyType::Kinematic)
	{
		// Both kinematic
		applyForce(bodyA, reaction * 0.5f);
		applyForce(bodyB, -reaction * 0.5f);
	}

	// Callbacks - On enter
	// TODO: Make enter be triggered only once
	if (bodyA.onEnter)
		bodyA.onEnter(bodyB);

	if (bodyB.onEnter)
		bodyB.onEnter(bodyA);
}

CollisionSolver::CollisionSolver()
{
	sphereColliders.reserve(256);
}

CollisionSolver::~CollisionSolver()
{

}

void CollisionSolver::update(float dt)
{
	Contact contact;

	// Sphere checks
	for (size_t a = 0; a < sphereColliders.size(); a++)
	{
		// Sphere
		for (size_t b = a + 1; b < sphereColliders.size(); b++)
		{
			Sphere& sphereA = *sphereColliders[a].get();
			Sphere& sphereB = *sphereColliders[b].get();

			if (overlapSphereSphere(sphereA, sphereB, &contact))
			{
				resolveSphereCollision(sphereA, sphereB, contact, dt);
			}
		}
	}
}