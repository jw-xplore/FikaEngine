#include "spritesheet_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void SpritesheetComponent::start()
{

}

void SpritesheetComponent::update(float dt)
{
	if (isAnimationPlaying)
	{
		playAnimation(dt);
	}
}

void SpritesheetComponent::onRemove()
{

}

nlohmann::json SpritesheetComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;

	return js;
}

void SpritesheetComponent::deserialize(nlohmann::json js)
{

}

void SpritesheetComponent::setupSheet(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	meshCmp = dynamic_cast<MeshComponent*>(FikaServers::getECSManager().findComponent(*owner, MeshComponent::componentId));
	assert(meshCmp);
	assert(meshCmp->getMeshInstance());

	glm::vec2 textureScale = glm::vec2(1.0f / columns, 1.0f / rows);

	meshCmp->getMeshInstance()->setTextureScale(textureScale);
}

void SpritesheetComponent::setCell(int column, int row)
{
	cell = glm::vec2(static_cast<float>(column), static_cast<float>(row));

	glm::vec2 textureScale = glm::vec2(1.0f / columns, 1.0f / rows);
	glm::vec2 textureOffset = glm::vec2(column * textureScale.x, row * textureScale.y);

	meshCmp->getMeshInstance()->setTextureOffset(textureOffset);
}

void SpritesheetComponent::playAnimation(float dt)
{
	animationTime += dt * animationFPS;
	if (animationTime > animationTimeline)
	{
		animationTime = animationTime - animationTimeline;
	}

	int position = (animationTime / animationTimeline) * columns;

	setCell(position, cell.y);
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

SpritesheetComponentUpdater::SpritesheetComponentUpdater()
{
}

void SpritesheetComponentUpdater::init(size_t poolSize)
{
	SpritesheetComponentUpdater* updater = new SpritesheetComponentUpdater();
	updater->components.init("Spritesheet Components", poolSize);
	updater->targetComponentId = SpritesheetComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void SpritesheetComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* SpritesheetComponentUpdater::addComponent()
{
	return components.allocate();
}

void SpritesheetComponentUpdater::removeComponent(ECSComponent& component)
{
	SpritesheetComponent* casted = static_cast<SpritesheetComponent*>(&component);
	assert(casted != nullptr);
	components.remove(casted);
}
