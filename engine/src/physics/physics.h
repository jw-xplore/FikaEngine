#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <memory>

struct Body
{
	int id;
	glm::mat4 transform;
	glm::vec3 velocity;
};

class PhysicsSolver
{
private:
	std::vector<std::unique_ptr<Body>> bodies;

public:
	PhysicsSolver();
	~PhysicsSolver();

	void update(float dt);

	Body& addBody();
};