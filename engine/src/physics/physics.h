#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include "collisions.h"

enum EBodyType
{
	Static,
	Kinematic
};

struct Body
{
	int id;
	EBodyType type = EBodyType::Kinematic;
	glm::mat4 transform;
	glm::vec3 velocity;
};

class PhysicsSolver
{
private:
	std::vector<std::unique_ptr<Body>> bodies;
	CollisionSolver collisionsSolver;

public:
	PhysicsSolver();
	~PhysicsSolver();

	void update(float dt);

	Body& addBody(const glm::mat4& tranform);

	CollisionSolver& getCollisionSolver() { return collisionsSolver; }
};