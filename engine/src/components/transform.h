#pragma once
#include <glm/glm.hpp>

class TransformComponent
{
	glm::mat4 transform;

public:
	TransformComponent();

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec4& rotation);
	void setScale(const glm::vec3& scale);
	void translate(const glm::vec3& translation);
	void rotate(const glm::vec4& rotation);

	glm::mat4& getTransform() { return transform; }
};