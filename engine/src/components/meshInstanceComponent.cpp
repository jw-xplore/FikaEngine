#include "meshInstanceComponent.h"
#include "../core/gameobject.h"
#include "../renderer/renderer.h"
#include "core/systemsHolder.h"

void MeshInstanceComponent::setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	instance = SystemsHolder::getInstance()->getMainRenderer()->addMeshInstance(&owner->getTransform(), meshRes, shader, texture);
}