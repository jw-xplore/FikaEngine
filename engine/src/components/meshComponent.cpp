#include "MeshComponent.h"
#include "core/fika_servers.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecsentity.h"
#include "core/transform.h"
#include "renderer/renderer.h"
#include <cassert>
#include "renderer/resources/gResourceManager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void MeshComponent::start()
{
	transform = FikaServers::getECSManager().findEntityTransform(*owner);
	assert(transform);
}

void MeshComponent::update(float dt)
{

}

nlohmann::json MeshComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;
	js["meshTag"] = instance->getMesh()->tag;
	js["meshPath"] = instance->getMesh()->sourcePath;
	js["textureTag"] = instance->getTexture()->tag;
	js["texturePath"] = instance->getTexture()->sourcePath;
	js["shaderTag"] = instance->gettShader()->tag;
	js["shaderVPath"] = instance->gettShader()->lastVpath;
	js["shaderFPath"] = instance->gettShader()->lastFpath;

	return js;
}

void MeshComponent::deserialize(nlohmann::json js)
{
	std::string meshStr = js["meshTag"];
	MeshResource& mesh = FikaServers::getGResourceManager().getMesh(meshStr);
	std::string texStr = js["textureTag"];
	TextureResource& texture = FikaServers::getGResourceManager().getTexture(texStr);
	std::string shaderStr = js["shaderTag"];
	ShaderResource& shader = FikaServers::getGResourceManager().getShader(shaderStr);

	setup(mesh, shader, &texture);
	setTexture(texture);
}

void MeshComponent::setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	instance = FikaServers::getMainRenderer().addMeshInstance(&transform->getGlobalTransform(), meshRes, shader, texture);
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

MeshComponentUpdater::MeshComponentUpdater()
{
}

void MeshComponentUpdater::init()
{
	MeshComponentUpdater* updater = new MeshComponentUpdater();
	updater->components = new PoolAllocator<MeshComponent>("Mesh Components");
	updater->targetComponentId = MeshComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void MeshComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* MeshComponentUpdater::addComponent()
{
	return components->allocate();
}
