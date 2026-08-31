#include "{{NAME}}Component.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void {{NAME}}Component::start()
{

}

void {{NAME}}Component::update(float dt)
{

}


//-------------------------------------------------------
// System
//-------------------------------------------------------

{{NAME}}ComponentUpdater::{{NAME}}ComponentUpdater()
{
}

void {{NAME}}ComponentUpdater::init()
{
	{{NAME}}ComponentUpdater* updater = new {{NAME}}ComponentUpdater();
	updater->components = new PoolAllocator<{{NAME}}Component>("TestCmp");
	updater->targetComponentId = {{NAME}}Component::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void {{NAME}}ComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

void {{NAME}}ComponentUpdater::addComponent()
{
	components->allocate();
}