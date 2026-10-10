#include "transform_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"

namespace FikaEngine
{
	//-------------------------------------------------------
	// Component
	//-------------------------------------------------------

	TransformComponent::TransformComponent(const glm::vec3& startPos)
	{
		transform.setPosition(startPos);
	}

	void TransformComponent::start()
	{

	}

	void TransformComponent::update(float dt)
	{

	}

	nlohmann::json TransformComponent::serialize()
	{
		nlohmann::json js = nlohmann::json::object();
		js["id"] = componentId;
		js["transform"] = transform.serialize();

		return js;
	}

	void TransformComponent::deserialize(nlohmann::json js)
	{
		transform.deserialize(js["transform"]);
	}

	//-------------------------------------------------------
	// System
	//-------------------------------------------------------

	TransformComponentUpdater::TransformComponentUpdater()
	{
	}

	void TransformComponentUpdater::init(size_t poolSize)
	{
		TransformComponentUpdater* updater = new TransformComponentUpdater();
		updater->components.init("Transform Components", poolSize);
		updater->targetComponentId = TransformComponent::componentId;

		FikaServers::getECSManager().registerUpdaters(updater);
	}

	void TransformComponentUpdater::update(float dt)
	{
		int size = components.getUsedAmount();

		for (size_t i = 0; i < size; i++)
		{
			components[i].update(dt);
		}
	}

	ECSComponent* TransformComponentUpdater::addComponent()
	{
		return components.allocate();
	}

	void TransformComponentUpdater::removeComponent(ECSComponent& component)
	{
		TransformComponent* casted = static_cast<TransformComponent*>(&component);
		assert(casted != nullptr);
		components.remove(casted);
	}

} // namespace FikaEngine
