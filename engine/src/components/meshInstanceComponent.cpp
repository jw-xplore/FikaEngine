#include "meshInstanceComponent.h"
#include "../core/gameobject.h"
#include "../renderer/renderer.h"

void MeshInstanceComponent::setup(MeshResource& meshRes, ShaderResource& shader)
{
	instance = Renderer::addMeshInstance(meshRes, shader);
}

void MeshInstanceComponent::start()
{
	//Renderer::addMeshInstance(*customMesh, basicShader);
}

void MeshInstanceComponent::update(float dt)
{
	instance->transform = owner->getTransform();
}