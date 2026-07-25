#include "contentManager.h"
#include "playerComponent.h"

ContentManager::ContentManager()
{
    // Setup resources
    cubeMesh = &GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
    basicShader = &GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    customMesh = GResourceManager::reserveMesh("custom1");
    MeshBuilder().loadMesh("assets/models/Sheep.obj").build(*customMesh);

    // Pawn
    MeshResource* pawnMesh = GResourceManager::reserveMesh("pawn");
    MeshBuilder().loadMesh("assets/models/pawn.obj").build(*pawnMesh);

    customTexture = &GResourceManager::reseveTexture("customTex1");
    customTexture->loadTexture("assets/textures/pawn.jpg");

    // Crate
    MeshResource* crateMesh = GResourceManager::reserveMesh("crate");
    MeshBuilder().loadMesh("assets/models/crate.obj").build(*crateMesh);

    TextureResource* crateTex = &GResourceManager::reseveTexture("crate");
    crateTex->loadTexture("assets/textures/crate.jpg");

    GResourceManager::debugPrint();
}

ContentManager::~ContentManager()
{

}

void ContentManager::createPlayer(glm::vec3 position)
{
    MeshResource& customMesh = GResourceManager::getMesh(GResourceManager::meshHandle("pawn"));
    TextureResource& customTexture = GResourceManager::getTexture(GResourceManager::textureHandle("customTex1"));
    ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    GameObject* player = FikaEngine::addGameObject();
    player->getTransformComponent().translate(position);
    MeshInstanceComponent* meshCmp = player->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, basicShader, nullptr);
    meshCmp->setTexture(customTexture);

    RigidbodyComponent* rb = player->addComponent<RigidbodyComponent>();
    //rb->setCollider(EColliderShape::ShapeSphere);
    rb->setCapsuleCollider(0.5, 1);

    player->addComponent<PlayerComponent>();
}

void ContentManager::createWall(glm::vec3 position, bool solid)
{
    MeshResource& customMesh = GResourceManager::getMesh(GResourceManager::meshHandle("crate"));
    TextureResource& customTexture = GResourceManager::getTexture(GResourceManager::textureHandle("crate"));

    GameObject* wall = FikaEngine::addGameObject();
    MeshInstanceComponent* meshCmp = wall->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, *basicShader, nullptr);
    meshCmp->setTexture(customTexture);
    wall->getTransformComponent().translate(position);
    RigidbodyComponent* wallRb = wall->addComponent<RigidbodyComponent>();

    if (solid)
        wallRb->setBodyType(EBodyType::Static);

    //wallRb->setBodyType(EBodyType::Trigger);
    wallRb->setBodyTag(1);
    //wallRb->setCollider(EColliderShape::ShapeSphere);
    //wallRb->setBoxCollider(glm::vec3(2.0f));
    wallRb->setBoxCollider(glm::vec3(2, 2, 2));
}