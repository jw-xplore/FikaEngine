#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

#include "contentManager.h"
#include "playerComponent.h"

MeshInstance cube0;
MeshInstance cube1;
ContentManager* contentManager;

void start()
{
    contentManager = new ContentManager();

    MeshResource* cubeMesh = &GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
    ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    //Renderer::addMeshInstance(*cubeMesh, basicShader);
    GResourceManager::debugPrint();
    
    // TODO: Fix storing and using of multiple mesh resources
    MeshResource* customMesh = GResourceManager::reserveMesh("custom1");
    GResourceManager::debugPrint();
    MeshBuilder().loadMesh("assets/models/testcharacter.obj").build(*customMesh);

    
    TextureResource& customTexture = GResourceManager::reseveTexture("customTex1");
    customTexture.loadTexture("assets/textures/testPlayer.jpg");
    //Renderer::addMeshInstance(*customMesh, basicShader);
    //Renderer::addMeshInstance(*cubeMesh, basicShader);

    // Setup camera
    CameraManager::getMainCamera()->move(glm::vec3(0, 2, -5), glm::vec3(0, 0, 1));

    // Player
    contentManager->createPlayer(glm::vec3(0));

    // Walls
    contentManager->createWall(glm::vec3(2, 0.5f, 0));
    contentManager->createWall(glm::vec3(2, 0.5f, 1));
    contentManager->createWall(glm::vec3(2, 0.5f, 2));
    contentManager->createWall(glm::vec3(2, 0.5f, 3));
    contentManager->createWall(glm::vec3(2, 0.5f, 4));
    contentManager->createWall(glm::vec3(2, 0.5f, 5));
    contentManager->createWall(glm::vec3(1, 0.5f, 5));
    contentManager->createWall(glm::vec3(0, 0.5f, 5));
    contentManager->createWall(glm::vec3(-1, 0.5f, 5));

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