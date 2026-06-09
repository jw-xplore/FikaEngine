#include "playerComponent.h"

void PlayerComponent::start()
{
    rb = owner->getComponent<RigidbodyComponent>();
}

void PlayerComponent::update(float dt)
{
    InputMapping* input = InputMapping::GetInstance();
    float forward = input->getAction("Vertical")->inputAxis();
    float right = input->getAction("Horizontal")->inputAxis();

    glm::vec3 velocity = glm::vec3(right, 0, forward) * speed;
    rb->setVelocity(velocity);
}