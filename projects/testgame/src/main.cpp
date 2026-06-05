#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "playerComponent.h"

MeshInstance cube0;
MeshInstance cube1;

void start()
{
    MeshResource* cubeMesh = &GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
    ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    //Renderer::addMeshInstance(*cubeMesh, basicShader);
    GResourceManager::debugPrint();
    
    // TODO: Fix storing and using of multiple mesh resources
    MeshResource* customMesh = GResourceManager::reserveMesh("custom1");
    GResourceManager::debugPrint();
    MeshBuilder().loadMesh("assets/models/testcharacter.obj").build(*customMesh);

    
    TextureResource* customTexture = GResourceManager::reseveTexture("customTex1");
    customTexture->loadTexture("assets/textures/testPlayer.jpg");
    //Renderer::addMeshInstance(*customMesh, basicShader);
    //Renderer::addMeshInstance(*cubeMesh, basicShader);

    // Setup camera
    CameraManager::getMainCamera()->move(glm::vec3(0, 2, -5), glm::vec3(0, 0, 1));

    // Setup testing player game object
    GameObject* player = GameObjectManager::addGameObject();
    MeshInstanceComponent* meshCmp = player->addComponent<MeshInstanceComponent>();
    meshCmp->setup(*customMesh, basicShader, customTexture);

    player->addComponent<PlayerComponent>();

    // Input mapping
    InputMapping::GetInstance();
}

void update(float dt)
{
    //GResourceManager::debugPrint();
    return;
}

int main()
{
    FikaEngine::run(start, update);
}