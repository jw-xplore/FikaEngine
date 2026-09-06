#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>
#include <fstream>

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
    //FikaECS::Entity& player = contentManager->createPlayer(glm::vec3(0, 0, 0));
    //FikaECS::Entity& wall = contentManager->createWall(glm::vec3(0,0,0), false);
    //contentManager->createWall(glm::vec3(2, 0, 0), false);

    //SystemsHolder::getECSManager()->makePrefab(player, "assets/prefabs/player.json");
    //SystemsHolder::getECSManager()->makePrefab(wall, "assets/prefabs/wall.json");

    // SystemsHolder::getECSManager()->loadEntities("entitiesTest.json");
    Prefab playerPref;
    SystemsHolder::getGameResourceManager()->loadPrefab("assets/prefabs/player.json", playerPref);
    SystemsHolder::getECSManager()->addEntityFromJson(playerPref.data);

    /*
    for (int i = 0; i < 1000; i++)
    {
        int x = rand() % 10;
        int z = rand() % 10;
        contentManager->createWall(glm::vec3(x, 0, z), false);
    }
    */

    // Test saving
    nlohmann::json entitiesJson = SystemsHolder::getECSManager()->serializeEntities();

    std::ofstream file("entitiesTest.json");

    if (!file.is_open())
    {
        std::cout << "Can't serialize game objects as levels folder/file is not found \n";
        return;
    }

    file << std::setw(4) << entitiesJson;
    file.close();
}

void update(float dt)
{

}

int main()
{
    FikaEngine::run(start, update);
}