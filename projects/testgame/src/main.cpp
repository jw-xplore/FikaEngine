#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "contentManager.h"
#include "playerComponent.h"

MeshInstance cube0;
MeshInstance cube1;
ContentManager* contentManager;

GameObject* player;
GameObject* wall;

void start()
{
    contentManager = new ContentManager();

    // Setup camera
    SystemsHolder* systemsHolder = SystemsHolder::getInstance();
    systemsHolder->getCameraManager()->getMainCamera()->move(glm::vec3(0, 4, -8), glm::vec3(0, -0.3f, 1));

    // Player
    player = &contentManager->createPlayer(glm::vec3(2, 0, 0));

    wall = &contentManager->createWall(glm::vec3(0, 0, 0), false);
    contentManager->createWall(glm::vec3(0, 0, 2), false);
    //contentManager->createWall(glm::vec3(2, 0, 0), true);
    
    player->getTransformComponent().addChild(wall->getTransformComponent());

    //wall->getTransformComponent().setPosition(glm::vec3(-2, 0, 0));
    //wall->getTransformComponent().setScale(glm::vec3(0.2));
    //player->getTransformComponent().setScale(glm::vec3(2));

    //player->getTransformComponent().setRotation(glm::vec3(0, 20, 0));

    // Walls
    //contentManager->createWall(glm::vec3(-4, 0, 2), false);
    //contentManager->createWall(glm::vec3(0, 0, 2), true);
    //contentManager->createWall(glm::vec3(4, 0, 2), false);

    /*
    for (int i = 0; i < 500; i++)
    {
        int x = rand() % 10;
        int z = rand() % 10;
        GameObject* go = &contentManager->createWall(glm::vec3(x, 0, z), false);
    }
    */

    // Input mapping
    InputMapping::GetInstance();
}

float rot = 0;
float pos = 0;

void update(float dt)
{
    //GResourceManager::debugPrint();
    rot -= dt * 100;
    pos = sin(dt * 100);
    //player->getTransformComponent().setRotation(glm::vec3(0, rot, 0));
    //wall->getTransformComponent().setRotation(glm::vec3(rot, 0, 0));
    //wall->getTransformComponent().setLocalRotation(glm::vec3(0, rot, 0));
    return;
}

int main()
{
    FikaEngine::run(start, update);
}