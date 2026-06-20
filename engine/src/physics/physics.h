#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include <string>
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
	unsigned int tag;
	EBodyType type = EBodyType::Kinematic;
	glm::mat4 transform;
	glm::vec3 velocity;
	EAxes freezeMovement = (EAxes)0;
	EAxes freezeRotation = (EAxes)0; // TODO: Add rotation freeze into force calculation and collisions

	// Callbacks
	std::function<void(Body&)> onEnter;
	std::function<void(Body&)> onExit;
};

void applyForce(Body& body, const glm::vec3& force);
void bodyFreezeMovement(Body& body, bool x, bool y, bool z);
void bodyFreezeRotation(Body& body, bool x, bool y, bool z);

class PhysicsSolver
{
private:
	CollisionSolver collisionsSolver;

	std::vector<std::unique_ptr<Body>> bodies;
	std::vector<std::string> tags;
	const const char* DEFAULT_TAG = "Default";

public:
	PhysicsSolver();
	~PhysicsSolver();

	void update(float dt);

	Body& addBody(const glm::mat4& tranform);

	CollisionSolver& getCollisionSolver() { return collisionsSolver; }

	int findTagId(std::string tag);
	int setTag(int position, std::string tag) { tags[position] = tag; }
};