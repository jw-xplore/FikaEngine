#include "meshInstanceComponent.h"
#include "../core/gameobject.h"
#include "../renderer/renderer.h"

void MeshInstanceComponent::setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	instance = Renderer::addMeshInstance(meshRes, shader, texture);
}

void MeshInstanceComponent::start()
{
	//Renderer::addMeshInstance(*customMesh, basicShader);
}

void MeshInstanceComponent::update(float dt)
{
	instance->transform = owner->getTransform();
}