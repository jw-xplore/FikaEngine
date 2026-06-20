#pragma once
#include "core/component.h"
#include "glm/glm.hpp"

enum EBodyType;
struct Body;
class Tranform;

enum EColliderShape
{
	ShapeSphere,
	ShapeBox
};

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
	void setBodyTag(int tag);
	void setCollider(EColliderShape shape);

	void onEnter(Body& body);
	void onExit(Body& body);
};