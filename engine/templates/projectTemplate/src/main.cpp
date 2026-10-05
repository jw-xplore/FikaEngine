#include <iostream>
#include <fika_engine.h>

using namespace FikaEngine;

void componentsInit()
{
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);
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