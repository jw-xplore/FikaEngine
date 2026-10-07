#include <iostream>
#include <fika_engine.h>

#include "core/content_manager.h"
#include "components/player_component.h"
#include "components/bullet_component.h"
#include "components/enemy_component.h"

/*
Project Fika Mayhem
*/

using namespace FikaEngine;

void componentsInit()
{
    // Engine components
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);

    // Custom components
    PlayerComponentUpdater::init(1);
    BulletComponentUpdater::init(POOL_DEFAULT_SIZE);
    EnemyComponentUpdater::init(POOL_DEFAULT_SIZE);
}

void start()
{
    componentsInit();

    ContentManager::createPlayer();
    
    ContentManager::createBox(glm::vec3(2, 0, 0));

    ContentManager::createEnemy(glm::vec3(4, 0, 3));
    ContentManager::createEnemy(glm::vec3(1, 0, 3));
    ContentManager::createEnemy(glm::vec3(-4, 0, 3));
    ContentManager::createEnemy(glm::vec3(4, 0, 2));
    ContentManager::createEnemy(glm::vec3(4, 0, -3));
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