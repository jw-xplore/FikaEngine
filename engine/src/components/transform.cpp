#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

inline glm::mat4 Transform::transformToMatrix()
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

inline void TransformComponent::applyToChildren()
{
    for (auto& child : children)
    {
        child->setTransformMatrix(transformMatrix);
        child->applyToChildren();
    }
}

void TransformComponent::setLocalPosition(const glm::vec3& position)
{
    localTransform.position = position;
    
    if (!parent)
    {
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        transformMatrix = parent->getTransformMatrix() * localTransform.transformToMatrix();
    }

    applyToChildren();
}

void TransformComponent::setLocalRotation(const glm::vec3& rotation)
{
    localTransform.rotation = rotation;

    if (!parent)
    {
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        transformMatrix = parent->getTransformMatrix() * localTransform.transformToMatrix();
    }

    applyToChildren();
}

void TransformComponent::setLocalScale(const glm::vec3& scale)
{
    localTransform.scale = scale;

    if (!parent)
    {
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        transformMatrix = parent->getTransformMatrix() * localTransform.transformToMatrix();
    }

    applyToChildren();
}

void TransformComponent::setPosition(const glm::vec3& position)
{
    if (!parent)
    {
        localTransform.position = position;
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        Transform tran = localTransform;
        tran.position = position;
        transformMatrix = tran.transformToMatrix();

        //localTransform.position = position - matrixToPosition(parent->getTransformMatrix());
        setTransformMatrix(transformMatrix - parent->getTransformMatrix());
    }

    applyToChildren();
}

void TransformComponent::setRotation(const glm::vec3& rotation)
{
    if (!parent)
    {
        localTransform.rotation = rotation;
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        Transform tran = localTransform;
        tran.rotation = rotation;
        transformMatrix = tran.transformToMatrix();

        localTransform.rotation = matrixToRotation(parent->getTransformMatrix() / transformMatrix);
    }

    applyToChildren();
}

void TransformComponent::setScale(const glm::vec3& scale)
{
    if (!parent)
    {
        localTransform.scale = scale;
        transformMatrix = localTransform.transformToMatrix();
    }
    else
    {
        Transform tran = localTransform;
        tran.scale = scale;
        transformMatrix = tran.transformToMatrix();

        localTransform.scale = matrixToScale(transformMatrix / parent->getTransformMatrix());
    }

    applyToChildren();
}

void TransformComponent::translate(const glm::vec3& translation)
{
    //transform = glm::translate(transform, translation);
    setPosition(localTransform.position + translation);
}

inline void TransformComponent::setTransformMatrix(const glm::mat4& mat)
{
    transformMatrix = mat * localTransform.transformToMatrix();
}

void TransformComponent::addChild(TransformComponent& child)
{
    child.parent = this;
    children.push_back(&child);
}

glm::vec3 TransformComponent::matrixToPosition(const glm::mat4& mat)
{
    return mat[3];
}

glm::vec3 TransformComponent::matrixToRotation(const glm::mat4& mat)
{
    const glm::vec3 left = glm::normalize(glm::vec3(mat[0])); // Normalized left axis
    const glm::vec3 up = glm::normalize(glm::vec3(mat[1])); // Normalized up axis
    const glm::vec3 forward = glm::normalize(glm::vec3(mat[2])); // Normalized forward axis

    // Obtain the "unscaled" transform matrix
    glm::mat4 m(0.0f);
    m[0][0] = left.x;
    m[0][1] = left.y;
    m[0][2] = left.z;

    m[1][0] = up.x;
    m[1][1] = up.y;
    m[1][2] = up.z;

    m[2][0] = forward.x;
    m[2][1] = forward.y;
    m[2][2] = forward.z;

    glm::vec3 rot;
    rot.x = atan2f(m[1][2], m[2][2]);
    rot.y = atan2f(-m[0][2], sqrtf(m[1][2] * m[1][2] + m[2][2] * m[2][2]));
    rot.z = atan2f(m[0][1], m[0][0]);
    rot = glm::degrees(rot); // Convert to degrees, or you could multiply it by (180.f / 3.14159265358979323846f)

    return rot;
}

glm::vec3 TransformComponent::matrixToScale(const glm::mat4& mat)
{
    glm::vec3 scale;
    scale.x = glm::length(glm::vec3(mat[0]));
    scale.y = glm::length(glm::vec3(mat[1]));
    scale.z = glm::length(glm::vec3(mat[2]));

    return scale;
}