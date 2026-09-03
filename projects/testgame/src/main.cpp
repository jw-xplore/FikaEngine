#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "contentManager.h"
#include "components/playerComponent.h"

ContentManager* contentManager;

void start()
{
    // Setup camera
    SystemsHolder* systemsHolder = SystemsHolder::getInstance();
    systemsHolder->getCameraManager()->getMainCamera()->move(glm::vec3(0, 4, -8), glm::vec3(0, -0.3f, 1));

    // Input mapping
    InputMapping::GetInstance();

    // Component updators inits
    TransformComponentUpdater::init();
    RigidBodyComponentUpdater::init();
    MeshComponentUpdater::init();
    PlayerComponentUpdater::init();
   
    // Test entity cmp setup
    contentManager = new ContentManager();
    contentManager->createPlayer(glm::vec3(0, 0, 0));
    contentManager->createWall(glm::vec3(2,0,0), false);

    /*
    for (int i = 0; i < 1000; i++)
    {
        int x = rand() % 10;
        int z = rand() % 10;
        contentManager->createWall(glm::vec3(x, 0, z), false);
    }
    */

}

void update(float dt)
{

}

int main()
{
    FikaEngine::run(start, update);
}