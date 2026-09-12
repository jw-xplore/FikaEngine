#pragma once
#include <vector>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include "core/pool_allocator.h"
#include "core/filemanagement/json.h"

class Transform;

//class SystemBase;
class Entity;
class ECSComponent;
class ComponentUpdater;

class ECSManager
{
private:
	PoolAllocator<Entity>* entities;
	std::vector<ComponentUpdater*> updaters;
	// Tracks which systems is used for component based on matching id
	std::map<unsigned int, ComponentUpdater*> componentIdUpdaters;
	// Entity-Component relation: entity id + component ids list
	std::map<unsigned int, std::vector<ECSComponent*>> entityComponets;

public:
	ECSManager() {}
	~ECSManager() {}

	void init();
	void update(float dt);

	int registerUpdaters(ComponentUpdater* system);
	Entity* addEntity(std::string name = "");
	ECSComponent* addComponent(Entity* entity, unsigned int componentId);
	ECSComponent* findComponent(Entity& entity, unsigned int componentId);
	Transform* findEntityTransform(Entity& entity);

	nlohmann::json serializeEntity(Entity& entity);
	void addEntityFromJson(nlohmann::json js);
	nlohmann::json serializeEntities();
	nlohmann::json serializeEditorEntities();
	void overrideJsonEntityTransform(nlohmann::json& jsonEntity, glm::mat4& transform);
	void loadEntities(const char* filePath);
};