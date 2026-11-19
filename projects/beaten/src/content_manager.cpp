#include "content_manager.h"
//#include "playerComponent.h"
#include <fstream>
#include <iostream>
#include "components/player_component.h"
#include "components/enemy_component.h"
#include "components/health_component.h"

ContentManager::ContentManager()
{
    
}

ContentManager::~ContentManager()
{

}

void ContentManager::init()
{
    GPUResourceManager& gResourceManager = FikaServers::getGPUResourceManager();
    ECSManager& ecsManager = FikaServers::getECSManager();

    // Crate
    gResourceManager.loadMesh("assets/models/crate.obj", "crate");
    gResourceManager.loadTexture("assets/textures/crate.jpg", "crate");

    gResourceManager.debugPrint();
}

Entity& ContentManager::createPlayer(glm::vec3 position)
{
    GPUResourceManager& gResourceManager = FikaServers::getGPUResourceManager();
    MeshResource& customMesh = gResourceManager.getMesh("quad");
    TextureResource* customTexture = gResourceManager.loadTexture("assets/textures/cobol.png", "char");
    ShaderResource& basicShader = gResourceManager.getShader("basic");

    ECSManager& ecsManager = FikaServers::getECSManager();

    Entity* entity = FikaServers::getECSManager().addEntity("player");

    // RB
    RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(ecsManager.addComponent(entity, RigidBodyComponent::componentId));
    //rb->setSphereCollider(1);
    rb->setCapsuleCollider(0.5, 2);
    rb->getTransform()->setPosition(position);
    rb->setLayers(2);

    // Mesh
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(ecsManager.addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, customTexture);
    meshCmp->setTexture(*customTexture);

    // Sprite sheet
    SpritesheetComponent* spriteSheetCmp = dynamic_cast<SpritesheetComponent*>(ecsManager.addComponent(entity, SpritesheetComponent::componentId));
    spriteSheetCmp->setupSheet(3, 8);
    spriteSheetCmp->addAnimation("attack", 5, 5);
    spriteSheetCmp->addAnimation("run", 5, 6);
    spriteSheetCmp->addAnimation("idle", 5, 6);

    //spriteSheetCmp->selectAnimation("run");
    spriteSheetCmp->setAnimationPlaying(true);

    // Melee
    MeleeComponent* meleeCmp = dynamic_cast<MeleeComponent*>(ecsManager.addComponent(entity, MeleeComponent::componentId));

    // Health
    HealthComponent* healthCmp = dynamic_cast<HealthComponent*>(ecsManager.addComponent(entity, HealthComponent::componentId));

    // Player
    ecsManager.addComponent(entity, PlayerComponent::componentId);
    
    return *entity;
}

Entity& ContentManager::createWall(glm::vec3 position, bool solid)
{
    GPUResourceManager& gResourceManager = FikaServers::getGPUResourceManager();
    MeshResource& customMesh = gResourceManager.getMesh("crate");
    TextureResource& customTexture = gResourceManager.getTexture("crate");
    ShaderResource& basicShader = gResourceManager.getShader("basic");

    ECSManager& ecsManager = FikaServers::getECSManager();

    Entity* entity = FikaServers::getECSManager().addEntity("wall");

    // RB
    RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(ecsManager.addComponent(entity, RigidBodyComponent::componentId));
    rb->setBoxCollider(glm::vec3(2));
    rb->setType(EBodyType::Static);
    if (!solid)
        rb->setType(EBodyType::Kinematic);
    rb->getTransform()->setPosition(position);
    rb->setInteractiveLayers(3);

    // Mesh
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(ecsManager.addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, &customTexture);
    meshCmp->setTexture(customTexture);

    return *entity;
}

Entity& ContentManager::createEnemy(glm::vec3 position)
{
    GPUResourceManager& gResourceManager = FikaServers::getGPUResourceManager();
    MeshResource& customMesh = gResourceManager.getMesh("quad");
    TextureResource* customTexture = gResourceManager.loadTexture("assets/textures/charidle.png", "enemy");
    ShaderResource& basicShader = gResourceManager.getShader("basic");

    ECSManager& ecsManager = FikaServers::getECSManager();

    Entity* entity = FikaServers::getECSManager().addEntity("player");

    // RB
    RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(ecsManager.addComponent(entity, RigidBodyComponent::componentId));
    //rb->setSphereCollider(1);
    rb->setCapsuleCollider(0.5, 2);
    rb->getTransform()->setPosition(position);
    rb->setLayers(1);

    // Mesh
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(ecsManager.addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, customTexture);
    meshCmp->setTexture(*customTexture);

    // Sprite sheet
    SpritesheetComponent* spriteSheetCmp = dynamic_cast<SpritesheetComponent*>(ecsManager.addComponent(entity, SpritesheetComponent::componentId));
    spriteSheetCmp->setupSheet(1, 2);
    spriteSheetCmp->addAnimation("idle", 1, 2);

    spriteSheetCmp->selectAnimation("idle");
    spriteSheetCmp->setAnimationPlaying(true);

    // Health
    HealthComponent* healthCmp = dynamic_cast<HealthComponent*>(ecsManager.addComponent(entity, HealthComponent::componentId));

    // Enemy
    ecsManager.addComponent(entity, EnemyComponent::componentId);

    return *entity;
}