#include "{{NAME}}Component.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

/*
Component
*/

void {{NAME}}Component::start()
{

}

void {{NAME}}Component::update(float dt)
{

}


/*
System
*/

{{NAME}}CmpUpdater::{{NAME}}CmpUpdater()
{
}

void {{NAME}}CmpUpdater::init()
{
	components = new PoolAllocator<{{NAME}}Component>("{{NAME}}Cmp", 256);
	targetComponentId = {{NAME}}Component::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(this);
}

void {{NAME}}CmpUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

void {{NAME}}CmpUpdater::addComponent()
{
	components->allocate();
}