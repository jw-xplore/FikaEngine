#include <iostream>
#include <fika_engine.h>

#include "content_manager.h"
#include "components/player_component.h"
#include "components/health_component.h"
#include "components/melee_component.h"
#include "components/enemy_component.h"
#include <ctime>

using namespace FikaEngine;

ContentManager contentManager;

void stressTest(int crates)
{
    const int max = 10;
    const int min = 0;

    for (size_t i = 0; i < crates; i++)
    {
        srand(static_cast<unsigned int>(std::time(nullptr)) + i);

        int x = rand() % (max - min + 1) + min;
        int z = rand() % (max - min + 1) + min;

        Entity& crate = contentManager.createWall(glm::vec3(x, 0, z), false);
    }
}

void componentsInit()
{
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);
    SpritesheetComponentUpdater::init(POOL_DEFAULT_SIZE);

    // Project components
    MeleeComponentUpdater::init(POOL_DEFAULT_SIZE);
    HealthComponentUpdater::init(POOL_DEFAULT_SIZE);
    PlayerComponentUpdater::init(1);
    EnemyComponentUpdater::init(POOL_DEFAULT_SIZE);

    contentManager.init();

    Entity& player = contentManager.createPlayer(glm::vec3(0, 0, 0));
    Entity& crate = contentManager.createWall(glm::vec3(0, 0, -2));

    Entity& enemy = contentManager.createEnemy(glm::vec3(4, 0, 0));
    Entity& enemy1 = contentManager.createEnemy(glm::vec3(-4, 0, 0));

    // Stress test
    stressTest(0);

    // UI test
    FikaServers::getMainRenderer().addUINode(glm::vec2(200, 100), glm::vec2(100, 0));
}

void start()
{
    componentsInit();
}

void update(float dt)
{

}

int main()
{
    FikaEngine::Game game;
    game.setup(start, update);
    game.run();
}