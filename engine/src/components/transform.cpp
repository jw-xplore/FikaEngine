#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

TransformComponent::TransformComponent()
{
    transform = glm::mat4(1.0f);
}

void TransformComponent::setPosition(const glm::vec3& position)
{
    transform[3] = glm::vec4(position.x, position.y, position.z, 1);
}

void TransformComponent::setRotation(const glm::vec4& rotation)
{
    // TODO
    //transform[3] = glm::vec4(position.x, position.y, position.z, 1);
}

void TransformComponent::setScale(const glm::vec3& scale)
{
    // TODO
}

void TransformComponent::translate(const glm::vec3& translation)
{
    transform = glm::translate(transform, translation);
}

void TransformComponent::rotate(const glm::vec4& rotation)
{
    // TODO
}