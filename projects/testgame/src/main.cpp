#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fikaEngine.h>

MeshInstance cube0;
MeshInstance cube1;

void start()
{
    MeshResource& cubeMesh = GResourceManager::getMesh(GResourceManager::meshHandle("cube"));
    ShaderResource& basicShader = GResourceManager::getShader(GResourceManager::shaderHandle("basic"));

    Renderer::addMeshInstance(cubeMesh, basicShader);
    MeshInstance* mi1 = Renderer::addMeshInstance(cubeMesh, basicShader);
    mi1->transform = glm::translate(mi1->transform, glm::vec3(0, 1, 0));
}

void update(float dt)
{
    return;
}

int main()
{
    Application app(start, update);
    app.run();
}