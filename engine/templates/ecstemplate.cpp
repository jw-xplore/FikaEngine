#include "{{NAME}}_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void {{NAME}}Component::start()
{

}

void {{NAME}}Component::update(float dt)
{

}

void {{NAME}}Component::onRemove()
{

}

nlohmann::json {{NAME}}Component::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void {{NAME}}Component::deserialize(nlohmann::json js)
{

}

//-------------------------------------------------------
// System
//-------------------------------------------------------

{{NAME}}ComponentUpdater::{{NAME}}ComponentUpdater()
{
}

void {{NAME}}ComponentUpdater::init(size_t poolSize)
{
	{{NAME}}ComponentUpdater* updater = new {{NAME}}ComponentUpdater();
	updater->components.init("{{NAME}} Components", poolSize);
	updater->targetComponentId = {{NAME}}Component::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void {{NAME}}ComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* {{NAME}}ComponentUpdater::addComponent()
{
	return components.allocate();
}

void {{NAME}}ComponentUpdater::removeComponent(ECSComponent& component)
{
	{{NAME}}Component* casted = static_cast<{{NAME}}Component*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}