#include "contentManager.h"
#include "playerComponent.h"

ContentManager::ContentManager()
{
    // Setup resources
    cubeMesh = &GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
    basicShader = &GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    customMesh = GResourceManager::reserveMesh("custom1");
    GResourceManager::debugPrint();
    MeshBuilder().loadMesh("assets/models/testcharacter.obj").build(*customMesh);


    customTexture = &GResourceManager::reseveTexture("customTex1");
    customTexture->loadTexture("assets/textures/testPlayer.jpg");
}

ContentManager::~ContentManager()
{

}

void ContentManager::createPlayer(glm::vec3 position)
{
    MeshResource& customMesh = GResourceManager::getMesh(GResourceManager::meshHandle("custom1"));
    TextureResource& customTexture = GResourceManager::getTexture(GResourceManager::textureHandle("customTex1"));
    ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    GameObject* player = FikaEngine::addGameObject();
    MeshInstanceComponent* meshCmp = player->addComponent<MeshInstanceComponent>();
    meshCmp->setup(customMesh, basicShader, nullptr);
    meshCmp->setTexture(customTexture);

    RigidbodyComponent* rb = player->addComponent<RigidbodyComponent>();
    rb->setCollider(EColliderShape::ShapeSphere);

    player->addComponent<PlayerComponent>();
}

void ContentManager::createWall(glm::vec3 position)
{
    GameObject* wall = FikaEngine::addGameObject();
    wall->addComponent<MeshInstanceComponent>()->setup(*cubeMesh, *basicShader, nullptr);
    wall->getTransformComponent().translate(position);
    RigidbodyComponent* wallRb = wall->addComponent<RigidbodyComponent>();
    wallRb->setBodyType(EBodyType::Static);
    //wallRb->setBodyType(EBodyType::Trigger);
    wallRb->setBodyTag(1);
    wallRb->setCollider(EColliderShape::ShapeBox);
}