#include "testComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"
#include <iostream>

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

TestCmpUpdater::TestCmpUpdater()
{
}

void TestCmpUpdater::init()
{
	TestCmpUpdater* updater = new TestCmpUpdater();
	updater->components = new PoolAllocator<TestComponent>("TestCmp");
	updater->targetComponentId = TestComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void TestCmpUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

void TestCmpUpdater::addComponent()
{
	components->allocate();
}