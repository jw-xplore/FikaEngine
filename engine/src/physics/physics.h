#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include "collisions.h"

enum EBodyType
{
	Static,
	Kinematic,
	Trigger,
};

enum EAxes
{
	X = 1,
	Y = 2,
	Z = 4,
};

struct Body
{
	int id;
	EBodyType type = EBodyType::Kinematic;
	glm::mat4 transform;
	glm::vec3 velocity;
	EAxes freezeMovement = (EAxes)0;
	EAxes freezeRotation = (EAxes)0; // TODO: Add rotation freeze into force calculation and collisions

	// Callbacks
	std::function<void(Body&)> onEnter;
};

void applyForce(Body& body, const glm::vec3& force);
void bodyFreezeMovement(Body& body, bool x, bool y, bool z);
void bodyFreezeRotation(Body& body, bool x, bool y, bool z);

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