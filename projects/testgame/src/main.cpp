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
    contentManager->createTestEntity();
    contentManager->createTestWall(glm::vec3(2,0,0));

    /*
    FikaECS::Entity* entity = SystemsHolder::getECSManager()->addEntity();
    TransformComponent* tranCmp = dynamic_cast<TransformComponent*>(SystemsHolder::getECSManager()->addComponent(entity, TransformComponent::componentId));
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(SystemsHolder::getECSManager()->addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, &customTexture);
    */

}

void update(float dt)
{

}

int main()
{
    FikaEngine::run(start, update);
}