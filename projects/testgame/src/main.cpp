#include <fika_engine.h>

#include "content_manager.h"
#include "components/player_component.h"

ContentManager contentManager;
using namespace FikaEngine;

void start()
{
    // Init order defines update order
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);
    SpritesheetComponentUpdater::init(POOL_DEFAULT_SIZE);

    PlayerComponentUpdater::init(1);
   
    // Test entity cmp setup
    contentManager.init();

    Entity& player = contentManager.createPlayer(glm::vec3(0, 0, 0));
    Entity& wall = contentManager.createWall(glm::vec3(2,0,0), true);
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