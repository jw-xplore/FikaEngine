#include <iostream>
#include <fika_engine.h>

#include "content_manager.h"
#include "components/player_component.h"

using namespace FikaEngine;

ContentManager contentManager;

void componentsInit()
{
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);
    SpritesheetComponentUpdater::init(POOL_DEFAULT_SIZE);

    PlayerComponentUpdater::init(1);

    contentManager.init();

    Entity& player = contentManager.createPlayer(glm::vec3(0, 0, 0));
    Entity& crate = contentManager.createWall(glm::vec3(2, 0, 0));
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