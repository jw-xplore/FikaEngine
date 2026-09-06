#pragma once
#include <glm/glm.hpp>
#include "core/filemanagement/json.h"

class Transform
{
private:
	glm::vec3 localPosition = glm::vec3(0.0);
	glm::vec3 localRotation = glm::vec3(0.0); // Euler
	glm::vec3 localScale = glm::vec3(1.0);
	glm::mat4 globalTransform = glm::mat4(1.0f);

	Transform* parent = nullptr;
	std::vector<Transform*> children;

	void localUpdate();

public:
	Transform() {}

	// Local
	glm::mat4 localToMatrix();
	inline glm::vec3 getLocalPosition() { return localPosition; }
	inline glm::vec3 getLocalRotation() { return localRotation; }
	inline glm::vec3 getLocalScale() { return localScale; }
	void setLocalPosition(const glm::vec3& position);
	void setLocalRotation(const glm::vec3& rotation);
	void setLocalScale(const glm::vec3& scale);

	// Global
	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setScale(const glm::vec3& scale);

	void translate(const glm::vec3& translation);

	void setGlobalTransform(const glm::mat4& mat);
	inline glm::mat4& getGlobalTransform() { return globalTransform; }

	static glm::vec3 matrixToPosition(const glm::mat4& mat);
	static glm::vec3 matrixToRotation(const glm::mat4& mat);
	static glm::vec3 matrixToScale(const glm::mat4& mat);

	nlohmann::json serialize();
	void deserialize(nlohmann::json js);
};