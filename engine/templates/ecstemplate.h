#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"

// Component
class {{NAME}}Component : public FikaECS::ECSComponent
{
public:
	{{NAME}}Component() {}
	static const unsigned int componentId = {{CMP_ID}}; // Do not change id
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

// System
class {{NAME}}CmpUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<{{NAME}}Component>* components;

public:
	{{NAME}}CmpUpdater();
	void init() override;
	void update(float dt) override;
	void addComponent() override;
};