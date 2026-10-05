#include <iostream>
#include <fika_engine.h>

using namespace FikaEngine;

void defaultComponentsInit()
{
    //TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    //RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    //MeshComponentUpdater::init(POOL_DEFAULT_SIZE);
}

void start()
{
    
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