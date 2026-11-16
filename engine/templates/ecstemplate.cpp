#include "{{FILE_NAME}}.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

const unsigned int {{CLASS_NAME}}Component::componentId;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void {{CLASS_NAME}}Component::start()
{

}

void {{CLASS_NAME}}Component::update(float dt)
{

}

void {{CLASS_NAME}}Component::onRemove()
{

}

nlohmann::json {{CLASS_NAME}}Component::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void {{CLASS_NAME}}Component::deserialize(nlohmann::json js)
{

}

//-------------------------------------------------------
// System
//-------------------------------------------------------

{{CLASS_NAME}}ComponentUpdater::{{CLASS_NAME}}ComponentUpdater()
{
}

void {{CLASS_NAME}}ComponentUpdater::init(size_t poolSize)
{
	{{CLASS_NAME}}ComponentUpdater* updater = new {{CLASS_NAME}}ComponentUpdater();
	updater->components.init("{{CLASS_NAME}} Components", poolSize);
	updater->targetComponentId = {{CLASS_NAME}}Component::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void {{CLASS_NAME}}ComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* {{CLASS_NAME}}ComponentUpdater::addComponent()
{
	return components.allocate();
}

void {{CLASS_NAME}}ComponentUpdater::removeComponent(ECSComponent& component)
{
	{{CLASS_NAME}}Component* casted = static_cast<{{CLASS_NAME}}Component*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}