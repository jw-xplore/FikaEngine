#pragma once
#include "glm/glm.hpp"
#include <memory>
#include "core/memorymanagement.h"

struct Body;

struct Sphere
{
	Body* body;
	float radius;
};

struct Box
{
	Body* body;
	glm::vec3 volume;
};

struct Capsule
{
	Body* body;
	float radius;
	float height;
};

struct Ray
{
	glm::vec3 start;
	glm::vec3 direction;
	float lenght;
	unsigned char interactiveLayers = 1;

	Ray(glm::vec3 start, glm::vec3 direction, float lenght): start(start), direction(direction), lenght(lenght)
	{
		if (direction != glm::vec3(0.0f))
			this->direction = glm::normalize(direction);
	}

	inline glm::vec3 end() const { return start + direction * lenght; }
};

struct Contact
{
	glm::vec3 normal;
	float penetration;
	glm::vec3 point;
};

const float PENETRATION_MULT = 0.0166f; // TODO: Adjust this with proper behavior and calculation

class CollisionSolver
{
private:
	PoolAllocator<Sphere>* sphereColliders;
	PoolAllocator<Box>* boxColliders;
	PoolAllocator<Capsule>* capsuleColliders;

	int bodiesCount = 0; // TODO: Do safer implementation
	bool* ongoingContacts = nullptr;

	const float targetDt = 1.0f / 60.0f;
	const int SOLVER_ITERATIONS = 3;
	const float MIN_DISTANCE = 1e-6f;

public:
	CollisionSolver();
	~CollisionSolver();

	void update(float dt);

	void resolveContact(Body& bodyA, Body& bodyB, Contact& contact);
	void checkCollsionExit(Body& bodyA, Body& bodyB);

	// Adding colliders
	Sphere* addSphereCollider(Body& body, float radius);
	Box* addBoxCollider(Body& body, glm::vec3 volume);
	Capsule* addCapsuleCollider(Body& body, float radius, float height);

	// Queries
	Contact* rayQuery(glm::vec3 start, glm::vec3 direction, float lenght);

	// Collisions
	// Sphere
	bool overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out = nullptr);
	// Box
	bool overlapBoxBox(const Box& colA, const Box& colB, Contact* out = nullptr);
	bool overlapSphereBox(const Sphere& colA, const Box& colB, Contact* out = nullptr);
	// Capsule
	bool overlapCapsuleCapsule(const Capsule& colA, const Capsule& colB, Contact* out = nullptr);
	bool overlapCapsuleSphere(const Capsule& colA, const Sphere& colB, Contact* out = nullptr);
	bool overlapCapsuleBox(const Capsule& colA, const Box& colB, Contact* out = nullptr);

	// Ray check
	bool overlapRaySphere(const Ray& ray, const Sphere& sphere, Contact* out = nullptr);
	bool overlapRayBox(const Ray& ray, const Box& box, Contact* out = nullptr);
	bool overlapRayCapsule(const Ray& ray, const Capsule& capsule, Contact* out = nullptr);
	bool updateAxis(float sAxis, float dAxis, float minAxis, float maxAxis, float& tEnter, float& tExit);

	void setupOngoinContacts(const size_t size);
	int contactFromPair(int bodyIdA, int bodyIdB);
};