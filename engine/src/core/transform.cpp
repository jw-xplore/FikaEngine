#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::localToMatrix()
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
        glm::radians(localRotation.x),
        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
        glm::radians(localRotation.y),
        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
        glm::radians(localRotation.z),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 rotationMat = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return  glm::translate(glm::mat4(1.0f), localPosition) *
            rotationMat *
            glm::scale(glm::mat4(1.0f), localScale);
}

void Transform::localUpdate()
{
    if (!parent)
    {
        setGlobalTransform(localToMatrix());
    }
    else
    {
        setGlobalTransform(parent->getGlobalTransform() * localToMatrix());
    }
}

void Transform::setLocalPosition(const glm::vec3& position)
{
    localPosition = position;
    localUpdate();
}

void Transform::setLocalRotation(const glm::vec3& rotation)
{
    localRotation = rotation;
    localUpdate();
}

void Transform::setLocalScale(const glm::vec3& scale)
{
    localScale = scale;
    localUpdate();
}

void Transform::setPosition(const glm::vec3& position)
{
    if (!parent)
    {
        setLocalPosition(position);
    }
    else
    {
        glm::vec3 pos = position;
        glm::vec3 rot = localRotation;
        glm::vec3 scale = localScale;

        glm::mat4 inv = glm::inverse(parent->getGlobalTransform());

        localPosition = matrixToPosition(inv) + position;
        setGlobalTransform(localToMatrix());
    }
}

void Transform::setRotation(const glm::vec3& rotation)
{
    if (!parent)
    {
        setLocalRotation(rotation);
    }
    else
    {
        glm::vec3 pos = localPosition;
        glm::vec3 rot = rotation;
        glm::vec3 scale = localScale;

        glm::mat4 inv = glm::inverse(parent->getGlobalTransform());

        localPosition = matrixToRotation(inv) + rotation;
        setGlobalTransform(localToMatrix());
    }
}

void Transform::setScale(const glm::vec3& scale)
{
    if (!parent)
    {
        setLocalScale(scale);
    }
    else
    {
        glm::vec3 pos = localPosition;
        glm::vec3 rot = localRotation;
        glm::vec3 scale = scale;

        glm::mat4 inv = glm::inverse(parent->getGlobalTransform());

        localPosition = matrixToScale(inv) + scale;
        setGlobalTransform(localToMatrix());
    }
}

void Transform::translate(const glm::vec3& translation)
{
    setLocalPosition(localPosition + translation);
}

void Transform::setGlobalTransform(const glm::mat4& mat)
{
    if (!parent)
    {
        globalTransform = mat;
    }
    else
    {
        globalTransform = mat * localToMatrix();
    }

    for (auto& child : children)
    {
        child->setGlobalTransform(globalTransform);
    }
}

glm::vec3 Transform::matrixToPosition(const glm::mat4& mat)
{
    return mat[3];
}

glm::vec3 Transform::matrixToRotation(const glm::mat4& mat)
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

glm::vec3 Transform::matrixToScale(const glm::mat4& mat)
{
    glm::vec3 scale;
    scale.x = glm::length(glm::vec3(mat[0]));
    scale.y = glm::length(glm::vec3(mat[1]));
    scale.z = glm::length(glm::vec3(mat[2]));

    return scale;
}

nlohmann::json Transform::serialize()
{
    nlohmann::json jsonMat = nlohmann::json::array();

    jsonMat.push_back(globalTransform[0][0]);
    jsonMat.push_back(globalTransform[0][1]);
    jsonMat.push_back(globalTransform[0][2]);
    jsonMat.push_back(globalTransform[0][3]);
    jsonMat.push_back(globalTransform[1][0]);
    jsonMat.push_back(globalTransform[1][1]);
    jsonMat.push_back(globalTransform[1][2]);
    jsonMat.push_back(globalTransform[1][3]);
    jsonMat.push_back(globalTransform[2][0]);
    jsonMat.push_back(globalTransform[2][1]);
    jsonMat.push_back(globalTransform[2][2]);
    jsonMat.push_back(globalTransform[2][3]);
    jsonMat.push_back(globalTransform[3][0]);
    jsonMat.push_back(globalTransform[3][1]);
    jsonMat.push_back(globalTransform[3][2]);
    jsonMat.push_back(globalTransform[3][3]);

    return jsonMat;
}

void Transform::deserialize(nlohmann::json)
{

}