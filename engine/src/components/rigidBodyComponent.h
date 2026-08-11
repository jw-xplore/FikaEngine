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

	// Body API
	void setVelocity(glm::vec3 velocity);
	void setBodyType(EBodyType type);
	void setBodyTag(int tag);
	void setLayers(unsigned char layers);
	void setInteractiveLayers(unsigned char layers);

	// Colliders
	void setCollider(EColliderShape shape);
	void setSphereCollider(float radius);
	void setBoxCollider(glm::vec3 volume);
	void setCapsuleCollider(float radius, float height);

	void onEnter(Body& body);
	void onExit(Body& body);
};