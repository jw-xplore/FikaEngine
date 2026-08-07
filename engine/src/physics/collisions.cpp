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
	sphereColliders = new PoolAllocator<Sphere>("Sphere colliders", 256);
	boxColliders = new PoolAllocator<Box>("Box colliders", 256);
	capsuleColliders = new PoolAllocator<Capsule>("Capsule colliders", 256);
}

CollisionSolver::~CollisionSolver()
{

}

void CollisionSolver::update(float dt)
{
	Contact contact;

	// Sphere checks
	for (size_t a = 0; a < sphereColliders->getUsedAmount(); a++)
	{
		Sphere& sphere = (*sphereColliders)[a];

		// Sphere
		for (size_t b = a + 1; b < sphereColliders->getUsedAmount(); b++)
		{
			Sphere& sphereB = (*sphereColliders)[b];

			if (overlapSphereSphere(sphere, sphereB, &contact))
			{
				resolveContact(*sphere.body, *sphereB.body, contact);
			}
		}

		// Box
		for (size_t b = 0; b < boxColliders->getUsedAmount(); b++)
		{
			Box& box = (*boxColliders)[b];

			if (overlapSphereBox(sphere, box, &contact))
			{
				resolveContact(*sphere.body, *box.body, contact);
			}
		}

		// Capsule
		for (size_t b = 0; b < capsuleColliders->getUsedAmount(); b++)
		{
			Capsule& capsule = (*capsuleColliders)[b];

			if (overlapCapsuleSphere(capsule, sphere, &contact))
			{
				resolveContact(*capsule.body, *sphere.body, contact);
			}
		}
	}

	// Box checks
	for (size_t a = 0; a < boxColliders->getUsedAmount(); a++)
	{
		Box& boxA = (*boxColliders)[a];

		// Box
		for (size_t b = a + 1; b < boxColliders->getUsedAmount(); b++)
		{
			Box& boxB = (*boxColliders)[b];

			if (overlapBoxBox(boxA, boxB, &contact))
			{
				resolveContact(*boxA.body, *boxB.body, contact);
			}
		}

		// Capsule
		for (size_t b = 0; b < capsuleColliders->getUsedAmount(); b++)
		{
			Capsule& capsule = (*capsuleColliders)[b];

			if (overlapCapsuleBox(capsule, boxA, &contact))
			{
				resolveContact(*capsule.body, *boxA.body, contact);
			}
		}
	}
}

Sphere* CollisionSolver::addSphereCollider(Body& body, float radius)
{
	// Collider
	Sphere* collider = sphereColliders->allocate();
	collider->body = &body;
	collider->radius = radius;

	// Debug
	MeshResource& cubeMesh = GResourceManager::getMesh(GResourceManager::meshHandle("sphere"));
	ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

	MeshInstance* mesh = SystemsHolder::getInstance()->getDebugRenderer()->addMeshInstance(&body.transform, cubeMesh, basicShader);
	mesh->customScale = glm::vec3(radius);

	// Return
	return &(*sphereColliders)[sphereColliders->getUsedAmount() - 1];
}

Box* CollisionSolver::addBoxCollider(Body& body, glm::vec3 volume)
{
	// Collider
	Box* collider = boxColliders->allocate();
	collider->body = &body;
	collider->volume = volume;

	// Debug
	MeshResource& cubeMesh = GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
	ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

	MeshInstance* mesh = SystemsHolder::getInstance()->getDebugRenderer()->addMeshInstance(&body.transform, cubeMesh, basicShader);
	mesh->customScale = glm::vec3(volume);

	// Return
	return &(*boxColliders)[boxColliders->getUsedAmount() - 1];
}

Capsule* CollisionSolver::addCapsuleCollider(Body& body, float radius, float height)
{
	// Collider
	Capsule* collider = capsuleColliders->allocate();
	collider->body = &body;
	collider->radius = radius;
	collider->height = height;

	// Debug
	MeshResource& debugMesh = GResourceManager::getMesh(GResourceManager::meshHandle("cylinder"));
	ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

	MeshInstance* mesh = SystemsHolder::getInstance()->getDebugRenderer()->addMeshInstance(&body.transform, debugMesh, basicShader);
	mesh->customScale = glm::vec3(radius, height, radius);

	return &(*capsuleColliders)[capsuleColliders->getUsedAmount() - 1];
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
			else                               normal = glm::vec3(0.0f, 0.0f, glm::sign(d.z));
		}

		// Penetration
		glm::vec3 volumeSum = (colA.volume + colB.volume) * 0.5f;
		volumeSum *= normal;

		glm::vec3 dNorm = d * normal;
		float dist = sqrt(glm::dot(dNorm, dNorm));

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

bool CollisionSolver::overlapSphereBox(const Sphere& colA, const Box& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	// Box
	float boxLeft = posB.x - colB.volume.x * 0.5f;
	float boxRight = posB.x + colB.volume.x * 0.5f;
	float boxBottom = posB.y - colB.volume.y * 0.5f;
	float boxTop = posB.y + colB.volume.y * 0.5f;
	float boxBack = posB.z - colB.volume.z * 0.5f;
	float boxFront = posB.z + colB.volume.z * 0.5f;

	// Find closest point
	glm::vec3 closestPoint;

	// x
	if (posA.x > boxRight)		closestPoint.x = boxRight;
	else if (posA.x < boxLeft)	closestPoint.x = boxLeft;
	else						closestPoint.x = posA.x;

	// y
	if (posA.y > boxTop)		closestPoint.y = boxTop;
	else if (posA.y < boxBottom)closestPoint.y = boxBottom;
	else						closestPoint.y = posA.y;

	// z
	if (posA.z > boxFront)		closestPoint.z = boxFront;
	else if (posA.z < boxBack)	closestPoint.z = boxBack;
	else						closestPoint.z = posA.z;

	// Check distance
	glm::vec3 pd = posA - closestPoint;
	float pDist2 = glm::dot(pd, pd);
	float r2 = colA.radius * colA.radius;

	if (pDist2 > r2)
		return false;

	if (out)
	{
		glm::vec3 normal;
		glm::vec3 a = glm::abs(pd);

		if (a.x >= a.y && a.x >= a.z)		normal = glm::vec3(glm::sign(pd.x), 0.0f, 0.0f);
		else if (a.y >= a.x && a.y >= a.z)	normal = glm::vec3(0.0f, glm::sign(pd.y), 0.0f);
		else								normal = glm::vec3(0.0f, 0.0f, glm::sign(pd.z));

		out->point = closestPoint;
		out->normal = normal;

		out->penetration = r2 - pDist2;
	}

	return true;
}

bool CollisionSolver::overlapCapsuleCapsule(const Capsule& colA, const Capsule& colB, Contact* out)
{
	// TODO
	return false;
}

bool CollisionSolver::overlapCapsuleSphere(const Capsule& colA, const Sphere& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	// Sphere distances check
	glm::vec3 d = posA - posB;
	d.y = 0;
	float dist2 = glm::dot(d, d);
	float rsum = colA.radius + colB.radius;

	// No distance collision?
	if (dist2 > rsum * rsum)
	{
		checkCollsionExit(*colA.body, *colB.body);
		return false;
	}

	// Height check
	float halfTotalHeight = colA.height * 0.5f + colA.radius;
	float ctop = posA.y + halfTotalHeight;
	float cbottom = posA.y - halfTotalHeight;

	float stop = posB.y + colB.radius;
	float sbottom = posB.y - colB.radius;

	// No height collision?
	if (cbottom > stop || ctop < sbottom)
	{
		checkCollsionExit(*colA.body, *colB.body);
		return false;
	}

	// Contact
	if (out)
	{
		float dist = std::sqrtf(dist2);
		glm::vec3 normal = dist > MIN_DISTANCE ? d / dist : glm::vec3(0, 1, 0);

		// Hemispheres handling
		float halfHeight = colA.height * 0.5f;
		float yDist = posB.y - posA.y;

		if (abs(yDist) > halfHeight)
		{
			float sphereYDist = abs(yDist) - halfHeight;
			int sign = 1;
			if (yDist < 0)
				sign = -1;

			d.y = sphereYDist * -sign;
			dist = std::sqrtf(glm::dot(d, d));

			// Sphere missing eachother
			if (dist > rsum)
			{
				checkCollsionExit(*colA.body, *colB.body);
				return false;
			}

			normal = dist > MIN_DISTANCE ? d / dist : glm::vec3(0, 1, 0);
		}

		float penetration = rsum - dist;

		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (colB.radius - penetration * 0.5f); // approx contact on B
	}

	return true;
}

bool CollisionSolver::overlapCapsuleBox(const Capsule& colA, const Box& colB, Contact* out)
{
	glm::vec3 posA = colA.body->transform[3];
	glm::vec3 posB = colB.body->transform[3];

	// Distance
	glm::vec3 d = posA - posB;
	d.y = 0;
	float dist2 = glm::dot(d, d);
	float radius2 = colA.radius * colA.radius;
	// NOTE: Cube longest is not correct
	float cubeLongest2 = colB.volume.x * colB.volume.x + colB.volume.y * colB.volume.y + colB.volume.z * colB.volume.z;

	// No distance collision?
	if (radius2 + cubeLongest2 < dist2)
	{
		checkCollsionExit(*colA.body, *colB.body);
		return false;
	}

	// Height comparison
	float halfTotalHeight = colA.height * 0.5f + colA.radius;
	float ctop = posA.y + halfTotalHeight;
	float cbottom = posA.y - halfTotalHeight;

	float boxTop = posB.y + colB.volume.y * 0.5f;
	float boxBottom = posB.y - colB.volume.y * 0.5f;

	// No height collision?
	if (cbottom > boxTop || ctop < boxBottom)
	{
		checkCollsionExit(*colA.body, *colB.body);
		return false;
	}
	// Box
	float boxLeft = posB.x - colB.volume.x * 0.5f;
	float boxRight = posB.x + colB.volume.x * 0.5f;
	float boxFront = posB.z + colB.volume.z * 0.5f;
	float boxBack = posB.z - colB.volume.z * 0.5f;

	// Contact
	if (out)
	{
		float dist = sqrt(dist2);

		// Set normal to allign with one of box sides
		glm::vec3 normal = glm::normalize(glm::vec3(d));

		if (d == glm::vec3(0.0f)) {
			normal = glm::vec3(0.0f);
		}
		else {
			glm::vec3 a = glm::abs(d);

			if (a.x >= a.y && a.x >= a.z)      normal = glm::vec3(glm::sign(d.x), 0.0f, 0.0f);
			else if (a.y >= a.x && a.y >= a.z) normal = glm::vec3(0.0f, glm::sign(d.y), 0.0f);
			else                                normal = glm::vec3(0.0f, 0.0f, glm::sign(d.z));
		}

		// Sphere touching the wall?
		if (normal.x != 0 && glm::abs(d.x) > colB.volume.x * 0.5f + colA.radius ||
			normal.y != 0 && glm::abs(d.y) > colB.volume.y * 0.5f + colA.radius ||
			normal.z != 0 && glm::abs(d.z) > colB.volume.z * 0.5f + colA.radius
			)
		{
			checkCollsionExit(*colA.body, *colB.body);
			return false;
		}

		// Penetration
		glm::vec3 volumeSum = colB.volume * 0.5f;
		volumeSum *= normal;

		//double volumeSuml = sqrt(volumeSum.x * volumeSum.x + volumeSum.y * volumeSum.y + volumeSum.z * volumeSum.z);
		float selectedVolume = colB.volume.x * 0.5f;
		if (normal.y != 0)
			selectedVolume = colB.volume.y * 0.5f;
		else if (normal.z != 0)
			selectedVolume = colB.volume.z * 0.5f;

		float penetration = (selectedVolume + colA.radius) - dist;
		if (penetration < 0)
			penetration = 0;

		out->normal = normal;
		out->penetration = penetration;
		//out->point = posB + normal * (colB.radius - penetration * 0.5f); // TODO
	}

	return true;
}

void CollisionSolver::setupOngoinContacts(const size_t size)
{
	if (ongoingContacts)
		delete ongoingContacts;

	bodiesCount = size;
	ongoingContacts = new bool[size * (size - 1) / 2];

	int i = 0;

	for (size_t a = 0; a < size; a++)
	{
		for (size_t b = a + 1; b < size; b++)
		{
			ongoingContacts[i] = false;
			i++;
		}
	}
}

int CollisionSolver::contactFromPair(int bodyIdA, int bodyIdB)
{
	// TODO: Check id matching between bodies, gos and contacts
	bodyIdA--;
	bodyIdB--;

	int a = bodyIdA * (2 * bodiesCount - bodyIdA - 1) / 2;
	int b = bodyIdB - bodyIdA - 1;
	return a + b;
}