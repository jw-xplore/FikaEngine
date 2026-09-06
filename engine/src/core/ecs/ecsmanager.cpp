#include "ecsmanager.h"
#include "ecscomponent.h"
#include "ecsentity.h"
#include <cassert>
#include "ecscomponentupdater.h"
#include "core/transform.h"
#include "components/transformComponent.h"
#include "components/rigidBodyComponent.h"
#include <fstream>

namespace FikaECS
{
	void ECSManager::init()
	{
		entities = new PoolAllocator<Entity>("entities");
		updaters.reserve(64);
	}

	void ECSManager::update(float dt)
	{
		for (auto& system : updaters)
		{
			system->update(dt);
		}
	}

	int ECSManager::registerUpdaters(ComponentUpdater* system)
	{
		int pos = updaters.size();
		updaters.push_back(system);

		componentIdUpdaters[system->getTargetComponentId()] = system;

		return pos;
	}

	Entity* ECSManager::addEntity()
	{
		return entities->allocate();
	}

	ECSComponent* ECSManager::addComponent(Entity* entity, unsigned int componentId)
	{
		bool systemExist = componentIdUpdaters.find(componentId) != componentIdUpdaters.end();
		if (!systemExist)
		{
			std::cout << "Fail to add component. System for id: " << componentId << " was never registered \n";
			std::cout << "Add system into ECSManager \n";
			assert(false);
		}

		// Add component to system
		ComponentUpdater* updater = componentIdUpdaters[componentId];
		ECSComponent* comp = updater->addComponent();
		updater->storeOwner(entity, comp);
		
		comp->setOwnerEntity(entity);
		comp->start();

		// Store relation
		entityComponets[entity->getId()].push_back(comp);

		return comp;
	}

	ECSComponent* ECSManager::findComponent(Entity& entity, unsigned int componentId)
	{
		return componentIdUpdaters[componentId]->getComponent(entity);
	}

	Transform* ECSManager::findEntityTransform(Entity& entity)
	{
		// Transform component
		ECSComponent* cmp = componentIdUpdaters[TransformComponent::componentId]->getComponent(entity);
		TransformComponent* transformCmp = static_cast<TransformComponent*>(cmp);
		if (transformCmp)
			return transformCmp->getTransform();

		// Rigidbody component
		cmp = componentIdUpdaters[RigidBodyComponent::componentId]->getComponent(entity);
		RigidBodyComponent* rbCmp = static_cast<RigidBodyComponent*>(cmp);
		if (rbCmp)
			return rbCmp->getTransform();
		
		return nullptr;
	}

	nlohmann::json ECSManager::serializeEntities()
	{
		size_t size = entities->getUsedAmount();
		nlohmann::json js = nlohmann::json::object();

		nlohmann::json jsonEntities = nlohmann::json::array();

		for (size_t i = 0; i < size; i++)
		{
			Entity entity = (*entities)[i];
			std::vector<ECSComponent*>& components = entityComponets[entity.getId()];

			nlohmann::json jsonEntity = nlohmann::json::object();
			nlohmann::json jsonComponents = nlohmann::json::array();

			for (ECSComponent*& comp : components)
			{
				nlohmann::json jsonCmp = comp->serialize();
				jsonComponents.push_back(jsonCmp);
			}

			jsonEntity["components"] = jsonComponents;
			jsonEntities.push_back(jsonEntity);
		}

		js["entities"] = jsonEntities;

		return js;
	}

	void ECSManager::loadEntities(const char* filePath)
	{
		// Read json
		std::ifstream file(filePath);
		if (!file.is_open())
		{
			std::cout << "Failed to load level \n";
			return;
		}

		// Parse data
		nlohmann::ordered_json jsonRes = nlohmann::ordered_json::parse(file);
		file.close();

		// Create entities
		nlohmann::json jsonEntities = jsonRes["entities"];
		for (auto& jsEnt : jsonEntities.items())
		{
			Entity* entity = addEntity();

			// Components
			nlohmann::json jsonComponents = jsEnt.value()["components"];

			for (auto& jsComp : jsonComponents.items())
			{
				unsigned int id = jsComp.value()["id"];
				ECSComponent* component = addComponent(entity, id);
				component->deserialize(jsComp.value());
			}
		}
	}
}