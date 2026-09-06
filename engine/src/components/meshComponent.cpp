#include "MeshComponent.h"
#include "core/systemsHolder.h"
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
	transform = SystemsHolder::getECSManager()->findEntityTransform(*owner);
	assert(transform);
}

void MeshComponent::update(float dt)
{

}

nlohmann::json MeshComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;
	js["mesh"] = instance->getMesh()->tag;
	js["texture"] = instance->getTexture()->tag;
	js["shader"] = instance->gettShader()->tag;

	return js;
}

void MeshComponent::deserialize(nlohmann::json js)
{
	std::string meshStr = js["mesh"];
	MeshResource& mesh = SystemsHolder::getGResourceManager()->getMesh(meshStr);
	std::string texStr = js["texture"];
	TextureResource& texture = SystemsHolder::getGResourceManager()->getTexture(texStr);
	std::string shaderStr = js["shader"];
	ShaderResource& shader = SystemsHolder::getGResourceManager()->getShader(shaderStr);

	setup(mesh, shader, &texture);
	setTexture(texture);
}

void MeshComponent::setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	instance = SystemsHolder::getInstance()->getMainRenderer()->addMeshInstance(&transform->getGlobalTransform(), meshRes, shader, texture);
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

	SystemsHolder::getECSManager()->registerUpdaters(updater);
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
