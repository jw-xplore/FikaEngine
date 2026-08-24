#include "contentManager.h"
#include "playerComponent.h"

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
    player->getTransformComponent().translate(position);
    MeshInstanceComponent* meshCmp = player->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, basicShader, nullptr);
    meshCmp->setTexture(customTexture);

    /*
    RigidbodyComponent* rb = player->addComponent<RigidbodyComponent>();
    //rb->setCollider(EColliderShape::ShapeSphere);
    rb->setCapsuleCollider(0.5f, 2);
    rb->setLayers(2);
    */

    player->addComponent<PlayerComponent>();
    
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
    wall->getTransformComponent().translate(position);

    /*
    RigidbodyComponent* wallRb = wall->addComponent<RigidbodyComponent>();

    if (solid)
        wallRb->setBodyType(EBodyType::Static);

    wallRb->setBodyType(EBodyType::Trigger);
    wallRb->setBodyTag(1);
    wallRb->setInteractiveLayers(3);

    //wallRb->setSphereCollider(1);
    wallRb->setBoxCollider(glm::vec3(2, 2, 2));
    //wallRb->setCapsuleCollider(0.5, 2);
    */

    return *wall;
}