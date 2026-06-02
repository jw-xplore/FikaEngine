#include "gameobject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject()
{
	lastGameObjectId++;
	id.id = lastGameObjectId;

    transform = glm::mat4(1.0);
}

void GameObject::removeComponent(Component* component)
{
    components.erase(
        std::remove_if(components.begin(), components.end(),
            [&](const std::unique_ptr<Component>& c)
            {
                return c.get() == component;
            }),
        components.end()
    );
}

void GameObject::setPosition(glm::vec3 position)
{
    transform[3] = glm::vec4(position.x, position.y, position.z, 1);
}

void GameObject::setRotation(glm::vec4 rotation)
{
    //transform[3] = glm::vec4(position.x, position.y, position.z, 1);
}

void GameObject::setScale(glm::vec3 scale)
{

}

void GameObject::translate(glm::vec3 translation)
{
    transform = glm::translate(transform, translation);
}

void GameObject::rotate(glm::vec4 rotation)
{

}