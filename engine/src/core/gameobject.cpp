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

nlohmann::json GameObject::serialize()
{
    nlohmann::json goJson = nlohmann::json::object();

    glm::vec3 pos = TransformComponent::matrixToPosition(transformComponent.getTransformMatrix());
    nlohmann::json posJson;
    posJson.push_back({ "x", pos.x });
    posJson.push_back({ "y", pos.y });
    posJson.push_back({ "z", pos.z });

    goJson.push_back({ "position", posJson });

    return goJson;
}