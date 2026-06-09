#pragma once
#include "glm/glm.hpp"

struct Sphere
{
	float radius;
};

struct Contact
{
	glm::vec3 normal;
	float penetration;
	glm::vec3 point;
};

bool overlapSphereSphere(const Sphere& colA, const glm::vec3& posA, const Sphere& colB, const glm::vec3& posB, Contact* out = nullptr);
void resolveSphereCollision(glm::mat4& tranA, glm::mat4& tranB, Contact& contact);

class CollisionSolver
{
private:
	const float targetDt = 1.0f / 60.0f;
	const int SOLVER_ITERATIONS = 3;

public:
	CollisionSolver();
	~CollisionSolver();

	void update(float dt);
};