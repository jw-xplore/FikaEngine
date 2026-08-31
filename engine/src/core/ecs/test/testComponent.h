#pragma once
#include "core/ecs/ecscomponent.h"
#include "core/ecs/ecscomponentupdater.h"
#include "core/memorymanagement.h"
#include <glm/glm.hpp>
#include <memory>

// Component
class TestComponent : public FikaECS::ECSComponent
{
public:
	glm::vec3 pos = glm::vec3(1, 2, 3);

	// Boilerplate
	TestComponent() {}
	static const unsigned int componentId = 123; // Should be assigned by generator
	unsigned int getComponentId() const override { return componentId; }
	void start() override;
	void update(float dt) override;
};

// System
class TestCmpUpdater : public FikaECS::ComponentUpdater
{
private:
	PoolAllocator<TestComponent>* components;

public:
	TestCmpUpdater();
	static void init();
	void update(float dt) override;
	FikaECS::ECSComponent* addComponent() override;
};