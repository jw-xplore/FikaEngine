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
    
    if (forward != 0 || right != 0)
        lastDirection = glm::vec3(right, 0, forward);

    glm::vec3 velocity = glm::vec3(right, 0, forward) * speed;
    rb->setVelocity(velocity);

    // Test line rendering
    /*
    SystemsHolder::getDebugRenderer()->addLine(Line(owner->getPosition(), owner->getPosition() + glm::vec3(2, 0, 0), glm::vec3(1,0,0)));
    SystemsHolder::getDebugRenderer()->addLine(Line(owner->getPosition(), owner->getPosition() + glm::vec3(0, 2, 0), glm::vec3(0,1,0)));
    SystemsHolder::getDebugRenderer()->addLine(Line(owner->getPosition(), owner->getPosition() + glm::vec3(0, 0, 2), glm::vec3(0,0,1)));
    */

    // Test raycast
    const float l = 2.0f;

    glm::vec3 rayColor = glm::vec3(1, 0, 0);
    bool hit = SystemsHolder::getPhysicsSolver()->getCollisionSolver().rayQuery(owner->getPosition(), lastDirection, l);
    if (hit)
        rayColor = glm::vec3(0, 1, 0);

    SystemsHolder::getDebugRenderer()->addLine(Line(owner->getPosition(), owner->getPosition() + lastDirection * l * glm::length(lastDirection), rayColor));
}