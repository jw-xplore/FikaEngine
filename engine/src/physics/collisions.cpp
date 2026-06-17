#include "collisions.h"
#include "physics.h"
#include "components/transform.h"
#include <glm/gtc/matrix_transform.hpp>

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

bool CollisionSolver::overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	glm::vec3 d = posA - posB;
	float dist2 = glm::dot(d, d);
	float rsum = colA.radius + colB.radius;
	float rsum2 = rsum * rsum;

	int contactId = contactFromPair(colA.body->id, colB.body->id);

	// No collision
	if (dist2 >= rsum)
	{
		ongoingContacts[contactId] = false;
		return false;
	}

	float dist = std::sqrtf(dist2);
	float penetration = rsum - dist;
	glm::vec3 normal = dist > MIN_DISTANCE ? d / dist : glm::vec3(0, 1, 0);

	if (out)
	{
		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (colB.radius - penetration * 0.5f); // approx contact on B
	}

	return true;
}

void CollisionSolver::resolveSphereCollision(Sphere& colA, Sphere& colB, Contact& contact, float dt)
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
	int contactId = contactFromPair(bodyA.id, bodyB.id);

	if (!ongoingContacts[contactId])
	{
		if (bodyA.onEnter)
			bodyA.onEnter(bodyB);

		if (bodyB.onEnter)
			bodyB.onEnter(bodyA);

		ongoingContacts[contactId] = true;
	}
}

bool CollisionSolver::overlapBoxBox(const Box& colA, const Box& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	// X
	float leftA = posA.x - colA.width * 0.5f;
	float leftB = posB.x - colB.width * 0.5f;
	float rightA = posA.x + colA.width * 0.5f;
	float rightB = posB.x + colB.width * 0.5f;

	// Y
	float bottomA = posA.y - colA.height * 0.5f;
	float bottomB = posB.y - colB.height * 0.5f;
	float topA = posA.y + colA.height * 0.5f;
	float topB = posB.y + colB.height * 0.5f;

	// Z
	float backA = posA.y - colA.depth * 0.5f;
	float backB = posB.y - colB.depth * 0.5f;
	float frontA = posA.y + colA.depth * 0.5f;
	float frontB = posB.y + colB.depth * 0.5f;

	// Compare
	bool isColliding = (
		leftA < rightB && leftB < rightA &&		// X
		bottomA < topB && bottomB < topA &&		// Y
		backA < frontB && backB < frontA		// Z
		);

	// Contact
	if (out && isColliding)
	{
		/*
		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (colB.radius - penetration * 0.5f);
		*/
	}

	return isColliding;
}

void CollisionSolver::setupOngoinContacts(const std::vector<std::unique_ptr<Body>>& bodies)
{
	ongoingContacts.clear();

	int size = bodies.size();
	bodiesCount = size;
	ongoingContacts.reserve(size * (size - 1) / 2);

	for (size_t a = 0; a < bodies.size(); a++)
	{
		for (size_t b = 0; b < bodies.size(); b++)
		{
			ongoingContacts.push_back(false);
		}
	}
}

int CollisionSolver::contactFromPair(int bodyIdA, int bodyIdB)
{
	int a = bodyIdA * (2 * bodiesCount - bodyIdA - 1) / 2;
	int b = bodyIdB - bodyIdA - 1;
	return a + b;
}