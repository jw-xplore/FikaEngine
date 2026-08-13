#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "contentManager.h"
#include "playerComponent.h"

MeshInstance cube0;
MeshInstance cube1;
ContentManager* contentManager;

void start()
{
    contentManager = new ContentManager();

    // Setup camera
    SystemsHolder* systemsHolder = SystemsHolder::getInstance();
    systemsHolder->getCameraManager()->getMainCamera()->move(glm::vec3(0, 4, -8), glm::vec3(0, -0.3f, 1));

    // Player
    contentManager->createPlayer(glm::vec3(2, 0, 2));

    // Walls
    //contentManager->createWall(glm::vec3(-4, 0, 2), false);
    contentManager->createWall(glm::vec3(0, 0, 2), true);
    //contentManager->createWall(glm::vec3(4, 0, 2), false);

    /*
    for (int i = 0; i < 500; i++)
    {
        int x = rand() % 10;
        int z = rand() % 10;
        contentManager->createWall(glm::vec3(x, 0, z), false);
    }
    */

    // Input mapping
    InputMapping::GetInstance();
}

void update(float dt)
{
    //GResourceManager::debugPrint();
    return;
}

int main()
{
    FikaEngine::run(start, update);
}