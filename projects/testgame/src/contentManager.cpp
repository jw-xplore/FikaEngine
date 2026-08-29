#include "contentManager.h"
#include "playerComponent.h"
#include <fstream>
#include <iostream>

ContentManager::ContentManager()
{
    gResourceManager = SystemsHolder::getInstance()->getGResourceManager();

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

GameObject& ContentManager::createPlayer(glm::vec3 position)
{
    MeshResource& customMesh = gResourceManager->getMesh("pawn");
    TextureResource& customTexture = gResourceManager->getTexture("customTex1");
    ShaderResource& basicShader = gResourceManager->getShader("basic");

    GameObject* player = FikaEngine::addGameObject();
    player->getTransformComponent().setPosition(position);
    MeshInstanceComponent* meshCmp = player->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, basicShader, nullptr);
    meshCmp->setTexture(customTexture);

    RigidbodyComponent* rb = player->addComponent<RigidbodyComponent>();
    //rb->setCollider(EColliderShape::ShapeSphere);
    rb->setCapsuleCollider(0.5f, 2);
    rb->setLayers(2);

    player->addComponent<PlayerComponent>();

    // Test print components
    //player->addComponent< 1722347611666756057>

    for (auto& comp : player->getComponents())
    {
        std::cout << "comp: " << typeid(*comp.get()).name() << ", code: " << comp.get()->componentID() << "\n";
        comp.get()->Deserialize((void*)&comp);
    }

    //player->Serialize();
    
    return *player;
}

GameObject& ContentManager::createWall(glm::vec3 position, bool solid)
{
    MeshResource& customMesh = gResourceManager->getMesh("crate");
    TextureResource& customTexture = gResourceManager->getTexture("crate");

    GameObject* wall = FikaEngine::addGameObject();
    MeshInstanceComponent* meshCmp = wall->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, *basicShader, nullptr);
    meshCmp->setTexture(customTexture);
    wall->getTransformComponent().setPosition(position);

    RigidbodyComponent* wallRb = wall->addComponent<RigidbodyComponent>();

    if (solid)
        wallRb->setBodyType(EBodyType::Static);

    wallRb->setBodyTag(1);
    wallRb->setInteractiveLayers(3);

    //wallRb->setSphereCollider(1);
    wallRb->setBoxCollider(glm::vec3(2, 2, 2));
    //wallRb->setCapsuleCollider(0.5, 2);

    return *wall;
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

        createWall(glm::vec3(x, y, z));
    }
}