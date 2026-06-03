#include "playerComponent.h"

void PlayerComponent::start()
{

}

void PlayerComponent::update(float dt)
{
    InputMapping* input = InputMapping::GetInstance();
    float forward = input->getAction("Vertical")->inputAxis();
    float right = input->getAction("Horizontal")->inputAxis();

    glm::vec3 tranlation = glm::vec3(right, 0, forward) * speed * dt;
    owner->translate(tranlation);
}