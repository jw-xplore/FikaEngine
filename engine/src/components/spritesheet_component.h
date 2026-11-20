#pragma once
#include "core/ecs/component.h"
#include "core/ecs/component_updater.h"
#include "core/pool_allocator.h"
#include "renderer/resources/gpu_resource_manager.h"
#include "mesh_component.h"
#include <map>

namespace FikaEngine
{
	struct SpriteSheetColumnAnim
	{
		float animationFPS = 1.0f;
		float animationTimeline = 1.0f;
		int cells = 1;
		int row = 0;
	};

	//-------------------------------------------------------
	// Component
	//-------------------------------------------------------

	/**
	 * @brief
	 */
	class SpritesheetComponent : public ECSComponent
	{
	private:
		MeshComponent* meshCmp;

		int rows = 1;
		int columns = 1;
		glm::vec2 cell = glm::vec2(0.0f);

		bool isAnimationPlaying = false;
		float animationTime = 0.0f;
		bool isAnimationLooping = false;

		SpriteSheetColumnAnim* activeAnimation = nullptr;
		std::map<std::string, SpriteSheetColumnAnim> animations;

		void playAnimation(float dt);

	public:
		SpritesheetComponent() {}
		static const unsigned int componentId = 5488; // Do not change id
		unsigned int getComponentId() const override { return componentId; }
		void start() override;
		void update(float dt) override;
		void onRemove() override;
		nlohmann::json serialize() override;
		void deserialize(nlohmann::json js) override;

		void setupSheet(int rows, int columns);
		void setCell(int column, int row);

		void setAnimationPlaying(bool playing) { isAnimationPlaying = playing; }
		SpriteSheetColumnAnim& addAnimation(std::string name, int cells, float timeline = 1.0f);
		void selectAnimation(std::string name);
		void setAnimationTime(float time);
		void setAnimationLooping(bool looping) { isAnimationLooping = looping; }
	};

	//-------------------------------------------------------
	// System
	//-------------------------------------------------------

	/**
	 * @brief Holds pool of SpritesheetComponent and run updates on them through ECS manager
	 */
	class SpritesheetComponentUpdater : public ComponentUpdater
	{
	private:
		PoolAllocator<SpritesheetComponent> components;

	public:
		SpritesheetComponentUpdater();

		/**
		 * @brief Call once at start to enable SpritesheetComponent pool update.
		 * Order of init call reflects in which order will updaters be processed.
		 */
		static void init(size_t poolSize);
		void update(float dt) override;
		ECSComponent* addComponent() override;
		void removeComponent(ECSComponent& component) override;
	};
}