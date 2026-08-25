#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0);
	glm::vec3 rotation = glm::vec3(0.0); // Euler
	glm::vec3 scale = glm::vec3(1.0);

	inline glm::mat4 transformToMatrix();
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

	inline void applyToChildren();

	// Local
	glm::vec3 getLocalPosition() { return localTransform.position; }
	void setLocalPosition(const glm::vec3& position);
	void setLocalRotation(const glm::vec3& rotation);
	void setLocalScale(const glm::vec3& scale);

	// Global
	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setScale(const glm::vec3& scale);
	void translate(const glm::vec3& translation);

	//glm::mat4& getTransform() { return transform; }
	inline void setTransformMatrix(const glm::mat4& mat);
	glm::mat4& getTransformMatrix() { return transformMatrix; }

	void addChild(TransformComponent& child);

	static glm::vec3 matrixToPosition(const glm::mat4& mat);
	static glm::vec3 matrixToRotation(const glm::mat4& mat);
	static glm::vec3 matrixToScale(const glm::mat4& mat);
};