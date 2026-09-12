#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fika_engine.h>
#include <fstream>

#include "content_manager.h"
#include "components/player_component.h"

ContentManager* contentManager;

void start()
{
    // Setup camera
    FikaServers::getCameraManager().getMainCamera()->move(glm::vec3(0, 4, -8), glm::vec3(0, -0.3f, 1));

    // Input mapping
    InputMapping::GetInstance();

    // Component updators inits
    TransformComponentUpdater::init();
    RigidBodyComponentUpdater::init();
    MeshComponentUpdater::init();
    PlayerComponentUpdater::init();
   
    // Test entity cmp setup
    contentManager = new ContentManager();
    Entity& player = contentManager->createPlayer(glm::vec3(0, 0, 0));
    Entity& wall = contentManager->createWall(glm::vec3(2,0,0), true);
    //contentManager->createWall(glm::vec3(2, 0, 0), false);

    //FikaServers::getGameResourceManager()->makePrefab(player, "assets/prefabs/player.json");
    //FikaServers::getGameResourceManager()->makePrefab(wall, "assets/prefabs/wall.json");

    //FikaServers::getECSManager().loadEntities("assets/levels/testLevel.json");

    // FikaServers::getECSManager().loadEntities("entitiesTest.json");
    Prefab playerPref;
    //FikaServers::getGameResourceManager()->loadPrefab("assets/prefabs/player.json", playerPref);
    //FikaServers::getECSManager().addEntityFromJson(playerPref.data);

    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 10;
        int z = rand() % 10;
        contentManager->createWall(glm::vec3(x, 0, z), false);
    }

    // Test saving
    /*
    nlohmann::json entitiesJson = FikaServers::getECSManager().serializeEntities();

    std::ofstream file("entitiesTest.json");

    if (!file.is_open())
    {
        std::cout << "Can't serialize game objects as levels folder/file is not found \n";
        return;
    }

    file << std::setw(4) << entitiesJson;
    file.close();
    */
}

void update(float dt)
{

}

int main()
{
    FikaEngine::Game game;
    game.run(start, update);
}