#pragma once
#include <memory>
#include <map>
#include <cstddef>
#include "core/pool_allocator.h"
#include "entity.h"
#include <iostream>
#include <cassert>

class ECSComponent;
class Entity;

/**
	* @brief Stores components of one specific types and runs their update.
	*/
class ComponentUpdater
{
protected:
	unsigned int targetComponentId = 0;
	std::map<unsigned int, ECSComponent*> entityOwnedComponents;

public:
	ComponentUpdater() {}
	virtual ~ComponentUpdater() {}

	virtual void update(float dt) {}
	virtual ECSComponent* addComponent() { return nullptr; }
	void storeOwner(Entity* entity, ECSComponent* component) { entityOwnedComponents[entity->getId()] = component; }

	unsigned int getTargetComponentId() { return targetComponentId; }
	ECSComponent* getComponent(Entity& entity) { return entityOwnedComponents[entity.getId()]; }
};