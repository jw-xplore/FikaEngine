#include "collisions.h"
#include "physics.h"
#include "components/transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/systemsHolder.h"
#include "renderer/renderer.h"
#include "renderer/resources/gResourceManager.h"
#include "renderer/resources/meshInstance.h"
#include <iostream>

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
				resolveContact(*sphereA.body, *sphereB.body, contact);
			}
		}
	}

	// Box checks
	for (size_t a = 0; a < boxColliders.size(); a++)
	{
		// Box
		for (size_t b = a + 1; b < boxColliders.size(); b++)
		{
			Box& boxA = *boxColliders[a].get();
			Box& boxB = *boxColliders[b].get();

			if (overlapBoxBox(boxA, boxB, &contact))
			{
				resolveContact(*boxA.body, *boxB.body, contact);
			}
		}
	}
}

Sphere* CollisionSolver::addSphereCollider(Body& body, float radius)
{
	// Collider
	auto collider = std::make_unique<Sphere>();
	collider.get()->body = &body;
	collider.get()->radius = radius;

	sphereColliders.push_back(std::move(collider));

	// Debug
	MeshResource& cubeMesh = GResourceManager::getMesh(GResourceManager::meshHandle("sphere"));
	ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

	MeshInstance* mesh = SystemsHolder::getInstance()->getDebugRenderer()->addMeshInstance(&body.transform, cubeMesh, basicShader);
	mesh->customScale = glm::vec3(radius);

	// Return
	return sphereColliders[sphereColliders.size() - 1].get();
}

Box* CollisionSolver::addBoxCollider(Body& body, glm::vec3 volume)
{
	// Collider
	auto collider = std::make_unique<Box>();
	collider.get()->body = &body;
	collider.get()->volume = volume;

	boxColliders.push_back(std::move(collider));

	// Debug
	MeshResource& cubeMesh = GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
	ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

	MeshInstance* mesh = SystemsHolder::getInstance()->getDebugRenderer()->addMeshInstance(&body.transform, cubeMesh, basicShader);
	mesh->customScale = glm::vec3(volume);

	// Return
	return boxColliders[boxColliders.size() - 1].get();
}

void CollisionSolver::addDebugMesh(glm::mat4& transform, float radius)
{
	SystemsHolder* systems = SystemsHolder::getInstance();

	
}

void CollisionSolver::resolveContact(Body& bodyA, Body& bodyB, Contact& contact)
{
	glm::vec3 reaction = contact.normal * contact.penetration;

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

void CollisionSolver::checkCollsionExit(Body& bodyA, Body& bodyB)
{
	// On leave callback
	int contactId = contactFromPair(bodyA.id, bodyB.id);

	if (ongoingContacts[contactId])
	{
		if (bodyA.onExit)
			bodyA.onExit(bodyB);

		if (bodyB.onExit)
			bodyB.onExit(bodyA);
	}

	ongoingContacts[contactId] = false;
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
	if (dist2 >= rsum2)
	{
		checkCollsionExit(*colA.body, *colB.body);
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

bool CollisionSolver::overlapBoxBox(const Box& colA, const Box& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	// X
	float leftA = posA.x - colA.volume.x * 0.5f;
	float leftB = posB.x - colB.volume.x * 0.5f;
	float rightA = posA.x + colA.volume.x * 0.5f;
	float rightB = posB.x + colB.volume.x * 0.5f;

	// Y
	float bottomA = posA.y - colA.volume.y * 0.5f;
	float bottomB = posB.y - colB.volume.y * 0.5f;
	float topA = posA.y + colA.volume.y * 0.5f;
	float topB = posB.y + colB.volume.y * 0.5f;

	// Z
	float backA = posA.z - colA.volume.z * 0.5f;
	float backB = posB.z - colB.volume.z * 0.5f;
	float frontA = posA.z + colA.volume.z * 0.5f;
	float frontB = posB.z + colB.volume.z * 0.5f;

	// Compare
	bool isColliding = (
		leftA < rightB && leftB < rightA &&		// X
		bottomA < topB && bottomB < topA &&		// Y
		backA < frontB && backB < frontA		// Z
		);

	// No collision
	if (!isColliding)
	{
		checkCollsionExit(*colA.body, *colB.body);
		return false;
	}

	// Contact
	if (out)
	{
		glm::vec3 d = posA - posB;
		float dist = sqrt(glm::dot(d, d));

		// TODO: Smooth collision at box edges

		// Set normal to allign with one of box sides
		glm::vec3 normal = glm::vec3(d);

		if (d == glm::vec3(0.0f)) {
			normal = glm::vec3(0.0f);
		}
		else {
			glm::vec3 a = glm::abs(d);

			if (a.x >= a.y && a.x >= a.z)      normal = glm::vec3(glm::sign(d.x), 0.0f, 0.0f);
			else if (a.y >= a.x && a.y >= a.z) normal = glm::vec3(0.0f, glm::sign(d.y), 0.0f);
			else                                normal = glm::vec3(0.0f, 0.0f, glm::sign(d.z));
		}

		// Penetration
		glm::vec3 volumeSum = (colA.volume + colB.volume) * 0.5f;
		volumeSum *= normal;

		double volumeSuml = sqrt(volumeSum.x * volumeSum.x + volumeSum.y * volumeSum.y + volumeSum.z * volumeSum.z);
		float penetration = volumeSuml - dist;
		if (penetration < 0)
			penetration = 0;

		out->normal = normal;
		out->penetration = penetration;
		//out->point = posB + normal * (colB.radius - penetration * 0.5f); // TODO
	}

	return true;
}

void CollisionSolver::setupOngoinContacts(const std::vector<std::unique_ptr<Body>>& bodies)
{
	ongoingContacts.clear();

	int size = bodies.size();
	bodiesCount = size;
	ongoingContacts.reserve(size * (size - 1) / 2);

	for (size_t a = 0; a < bodies.size(); a++)
	{
		for (size_t b = a + 1; b < bodies.size(); b++)
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