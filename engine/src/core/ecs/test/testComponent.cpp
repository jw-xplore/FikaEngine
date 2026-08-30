#include "testComponent.h"
#include <iostream>
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

/*
Component
*/

void TestComponent::start()
{
	std::cout << "Test cmp start \n";
}

void TestComponent::update(float dt)
{
	std::cout << "spam";
}


/*
System
*/

TestSystem::TestSystem()
{
}

void TestSystem::init()
{
	components = new PoolAllocator<TestComponent>("TestCmp", 256);
	targetComponentId = TestComponent::componentId;

	SystemsHolder::getECSManager()->registerSystem(this);
}

void TestSystem::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

void TestSystem::addComponent()
{
	components->allocate();
}