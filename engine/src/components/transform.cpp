#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::transformToMatrix()
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
        glm::radians(rotation.x),
        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
        glm::radians(rotation.y),
        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
        glm::radians(rotation.z),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 rotationMat = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return  glm::translate(glm::mat4(1.0f), position) *
            rotationMat *
            glm::scale(glm::mat4(1.0f), scale);
}

TransformComponent::TransformComponent()
{
    //
}

void TransformComponent::setPosition(const glm::vec3& position)
{
    //transform[3] = glm::vec4(position.x, position.y, position.z, 1);
    
    if (!parent)
    {
        localTransform.position = position;
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        //transformMatrix = transformMatrix + localTransform.transformToMatrix();
    }

    for (auto& child : children)
    {
       // child->setPosition(child->getLocalPosition() + localTransform.position);
        child->setTransformMatrix(transformMatrix);
    }
}

void TransformComponent::translate(const glm::vec3& translation)
{
    //transform = glm::translate(transform, translation);
    setPosition(localTransform.position + translation);
}

void TransformComponent::setTransformMatrix(const glm::mat4& mat)
{
    glm::mat4 local = localTransform.transformToMatrix();
    transformMatrix = mat * local;
}

void TransformComponent::addChild(TransformComponent& child)
{
    child.parent = this;
    children.push_back(&child);
}