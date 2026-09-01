/*
#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include <string>
#include "collisions.h"
#include "core/memorymanagement.h"

class TransformComponent;

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
	unsigned int tag = 0;
	unsigned char layers = 1;
	unsigned char interactiveLayers = 1; // Enables collisions with objects in matching layers
	EBodyType type = EBodyType::Kinematic;
	glm::mat4 transform = glm::mat4(1.0);
	glm::vec3 velocity = glm::vec3(0.0);
	EAxes freezeMovement = (EAxes)0;
	EAxes freezeRotation = (EAxes)0; // TODO: Add rotation freeze into force calculation and collisions

	// Callbacks
	std::function<void(Body&)> onEnter;
	std::function<void(Body&)> onExit;

	void onParentTransformUpdate(glm::mat4& transform);
};

void applyForce(Body& body, const glm::vec3& force);
void bodyFreezeMovement(Body& body, bool x, bool y, bool z);
void bodyFreezeRotation(Body& body, bool x, bool y, bool z);

class PhysicsSolver
{
private:
	CollisionSolver collisionsSolver;

	PoolAllocator<Body>* bodies;
	std::vector<std::string> tags;
	std::vector<std::string> layers;
	const const char* DEFAULT_TAG = "Default";
	const const char* DEFAULT_LAYER = "Default";
	const const char* PLAYER_LAYER = "Player";

public:
	PhysicsSolver();
	~PhysicsSolver();

	void update(float dt);

	Body& addBody(TransformComponent& tranform);

	CollisionSolver& getCollisionSolver() { return collisionsSolver; }

	int findTagId(std::string tag);
	int setTag(int position, std::string tag) { tags[position] = tag; }
	std::string getTagName(int position) { return tags[position]; }
	static bool canCheckCollision(const Body& body, const Body& target);
};

*/