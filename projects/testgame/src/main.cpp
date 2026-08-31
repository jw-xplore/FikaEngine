#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "contentManager.h"
#include "playerComponent.h"

void start()
{
    // Setup camera
    SystemsHolder* systemsHolder = SystemsHolder::getInstance();
    systemsHolder->getCameraManager()->getMainCamera()->move(glm::vec3(0, 4, -8), glm::vec3(0, -0.3f, 1));

    // Input mapping
    InputMapping::GetInstance();
}

void update(float dt)
{

}

int main()
{
    FikaEngine::run(start, update);
}