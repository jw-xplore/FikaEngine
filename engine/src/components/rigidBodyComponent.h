#pragma once
#include "core/component.h"
#include "glm/glm.hpp"

enum EBodyType;
struct Body;
class Tranform;

class RigidbodyComponent : public Component
{
private:
	Body* body;
	glm::mat4* transform;

public:
	RigidbodyComponent() {}

	void start() override;
	void update(float dt) override;

	void setVelocity(glm::vec3 velocity);
	void setBodyType(EBodyType type);
};