#pragma once
#include "glm/glm.hpp"
#include <memory>

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
	std::vector<std::unique_ptr<Sphere>> sphereColliders;
	std::vector<std::unique_ptr<Box>> boxColliders;
	int bodiesCount = 0; // TODO: Do safer implementation
	std::vector<bool> ongoingContacts;

	const float targetDt = 1.0f / 60.0f;
	const int SOLVER_ITERATIONS = 3;
	const float MIN_DISTANCE = 1e-6f;

public:
	CollisionSolver();
	~CollisionSolver();

	void update(float dt);

	Sphere* addSphereCollider(Body& body, float radius);
	Box* addBoxCollider(Body& body, glm::vec3 volume);

	void addDebugMesh(glm::mat4& transform, float radius = 1);

	void resolveContact(Body& bodyA, Body& bodyB, Contact& contact);
	void checkCollsionExit(Body& bodyA, Body& bodyB);

	bool overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out = nullptr);
	bool overlapBoxBox(const Box& colA, const Box& colB, Contact* out = nullptr);

	void setupOngoinContacts(const std::vector<std::unique_ptr<Body>>& bodies);
	int contactFromPair(int bodyIdA, int bodyIdB);
};