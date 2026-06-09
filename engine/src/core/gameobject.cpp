#include "gameobject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject()
{
	lastGameObjectId++;
	id.id = lastGameObjectId;
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