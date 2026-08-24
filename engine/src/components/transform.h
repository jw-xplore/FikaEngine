#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0);
	glm::vec3 rotation = glm::vec3(0.0); // Euler
	glm::vec3 scale = glm::vec3(1.0);

	glm::mat4 transformToMatrix();
};

class TransformComponent
{
private:
	Transform localTransform;
	//glm::mat4 transform;
	glm::mat4 transformMatrix = glm::mat4(1.0f);

	TransformComponent* parent = nullptr;
	std::vector<TransformComponent*> children;

public:
	TransformComponent();

	glm::vec3 getLocalPosition() { return localTransform.position; }

	void setPosition(const glm::vec3& position);
	void translate(const glm::vec3& translation);

	//glm::mat4& getTransform() { return transform; }
	void setTransformMatrix(const glm::mat4& mat);
	glm::mat4& getTransformMatrix() { return transformMatrix; }

	void addChild(TransformComponent& child);
};