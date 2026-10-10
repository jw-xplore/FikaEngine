#include "mesh_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "core/transform.h"
#include "renderer/renderer.h"
#include <cassert>
#include "renderer/resources/gpu_resource_manager.h"

namespace FikaEngine
{
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

	void MeshComponent::onRemove()
	{
		if (instance != nullptr)
		{
			FikaServers::getMainRenderer().removeMeshIntance(*instance);
		}
	}

	nlohmann::json MeshComponent::serialize()
	{
		nlohmann::json js = nlohmann::json::object();
		js["id"] = componentId;

		std::string meshTag = "";
		std::string meshSourcePath = "";
		std::string textureTag = "";
		std::string textureSourcePath = "";
		std::string shaderTag = "";
		std::string shaderVPath = "";
		std::string shaderFPath = "";

		if (instance->getMesh())
		{
			meshTag = instance->getMesh()->tag;
			meshSourcePath = instance->getMesh()->sourcePath;
		}

		if (instance->getTexture())
		{
			textureTag = instance->getTexture()->tag;
			textureSourcePath = instance->getTexture()->sourcePath;
		}

		if (instance->gettShader())
		{
			shaderTag = instance->gettShader()->tag;
			shaderVPath = instance->gettShader()->lastVpath;
			shaderFPath = instance->gettShader()->lastFpath;
		}

		js["meshTag"] = meshTag;
		js["meshPath"] = meshSourcePath;
		js["textureTag"] = textureTag;
		js["texturePath"] = textureSourcePath;
		js["shaderTag"] = shaderTag;
		js["shaderVPath"] = shaderVPath;
		js["shaderFPath"] = shaderFPath;

		return js;
	}

	void MeshComponent::deserialize(nlohmann::json js)
	{
		std::string meshStr = js["meshTag"];
		MeshResource& mesh = FikaServers::getGPUResourceManager().getMesh(meshStr);
		std::string texStr = js["textureTag"];
		TextureResource& texture = FikaServers::getGPUResourceManager().getTexture(texStr);
		std::string shaderStr = js["shaderTag"];
		ShaderResource& shader = FikaServers::getGPUResourceManager().getShader(shaderStr);

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

	void MeshComponentUpdater::init(size_t poolSize)
	{
		MeshComponentUpdater* updater = new MeshComponentUpdater();
		updater->components.init("Mesh Components", poolSize);
		updater->targetComponentId = MeshComponent::componentId;

		FikaServers::getECSManager().registerUpdaters(updater);
	}

	void MeshComponentUpdater::update(float dt)
	{
		int size = components.getUsedAmount();

		for (size_t i = 0; i < size; i++)
		{
			components[i].update(dt);
		}
	}

	ECSComponent* MeshComponentUpdater::addComponent()
	{
		return components.allocate();
	}

	void MeshComponentUpdater::removeComponent(ECSComponent& component)
	{
		MeshComponent* casted = static_cast<MeshComponent*>(&component);
		assert(casted != nullptr);
		components.remove(casted);
	}
} // namespace FikaEngine
