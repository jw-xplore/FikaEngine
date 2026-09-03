#include "contentManager.h"
//#include "playerComponent.h"
#include <fstream>
#include <iostream>
#include "components/playerComponent.h"

ContentManager::ContentManager()
{
    gResourceManager = SystemsHolder::getGResourceManager();
    ecsManager = SystemsHolder::getECSManager();

    // Setup resources
    cubeMesh = &gResourceManager->getMesh("cube");
    basicShader = &gResourceManager->getShader("basic");

    customMesh = gResourceManager->reserveMesh("custom1");
    MeshBuilder().loadMesh("assets/models/Sheep.obj").build(*customMesh);

    // Pawn
    MeshResource* pawnMesh = gResourceManager->reserveMesh("pawn");
    MeshBuilder().loadMesh("assets/models/pawn.obj").build(*pawnMesh);

    customTexture = &gResourceManager->reseveTexture("customTex1");
    customTexture->loadTexture("assets/textures/pawn.jpg");

    // Crate
    MeshResource* crateMesh = gResourceManager->reserveMesh("crate");
    MeshBuilder().loadMesh("assets/models/crate.obj").build(*crateMesh);

    TextureResource* crateTex = &gResourceManager->reseveTexture("crate");
    crateTex->loadTexture("assets/textures/crate.jpg");

    gResourceManager->debugPrint();
}

ContentManager::~ContentManager()
{

}

FikaECS::Entity& ContentManager::createPlayer(glm::vec3 position)
{
    GResourceManager* gResourceManager = SystemsHolder::getInstance()->getGResourceManager();
    MeshResource& customMesh = gResourceManager->getMesh("pawn");
    TextureResource& customTexture = gResourceManager->getTexture("customTex1");
    ShaderResource& basicShader = gResourceManager->getShader("basic");

    FikaECS::Entity* entity = SystemsHolder::getECSManager()->addEntity();

    // RB
    RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(ecsManager->addComponent(entity, RigidBodyComponent::componentId));
    rb->setSphereCollider(1);
    rb->getTransform()->setPosition(position);

    // Mesh
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(ecsManager->addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, &customTexture);
    meshCmp->setTexture(customTexture);

    // Player
    ecsManager->addComponent(entity, PlayerComponent::componentId);
    
    return *entity;
}

FikaECS::Entity& ContentManager::createWall(glm::vec3 position, bool solid)
{
    GResourceManager* gResourceManager = SystemsHolder::getInstance()->getGResourceManager();
    MeshResource& customMesh = gResourceManager->getMesh("crate");
    TextureResource& customTexture = gResourceManager->getTexture("crate");
    ShaderResource& basicShader = gResourceManager->getShader("basic");

    FikaECS::Entity* entity = SystemsHolder::getECSManager()->addEntity();

    // RB
    RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(ecsManager->addComponent(entity, RigidBodyComponent::componentId));
    rb->setSphereCollider(1);
    rb->setType(EBodyType::Static);
    if (!solid)
        rb->setType(EBodyType::Kinematic);
    rb->getTransform()->setPosition(position);

    // Mesh
    MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(ecsManager->addComponent(entity, MeshComponent::componentId));
    meshCmp->setup(customMesh, basicShader, &customTexture);
    meshCmp->setTexture(customTexture);

    return *entity;
}

void ContentManager::loadWalls(const char* filePath)
{
    // Read json
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Failed to load level \n";
        return;
    }

    // Parse data
    nlohmann::ordered_json jsonRes = nlohmann::ordered_json::parse(file);
    file.close();

    nlohmann::json level = jsonRes["level"];
    for (auto& item : level.items())
    {
        nlohmann::json position = item.value()["position"];

        float x = position["x"];
        float y = position["y"];
        float z = position["z"];

        //createWall(glm::vec3(x, y, z));
    }
}