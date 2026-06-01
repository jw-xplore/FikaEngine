#include "playerComponent.h"

void PlayerComponent::start()
{
	keyboard = Input::getDefaultKeyboard();
    //meshInstance = 
}

void PlayerComponent::update(float dt)
{
    // TODO: Implement controls using input mapping

    // Forwards - backwards
    float forward = 0;
    if (keyboard->held[Input::Key::W])
        forward = 1;
    if (keyboard->held[Input::Key::S])
        forward = -1;

    // Sides
    float right = 0;
    if (keyboard->held[Input::Key::D])
        right = 1;
    if (keyboard->held[Input::Key::A])
        right = -1;

    // Move
    //position += glm::vec3(0,0,-1) * forward * speed;
    //position += glm::vec3(1,0,0) * right * speed;
}