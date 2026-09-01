#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace FikaECS
{
	class Entity;

	class ECSComponent
	{
	protected:
		Entity* owner;

	public:
		ECSComponent() {}
		virtual ~ECSComponent() {}

		/**
		 * @brief Called when Component is added.
		 */
		virtual void start() {}

		/**
		 * @brief Called each frame.
		 * @param dt
		 */
		virtual void update(float dt) {}

		virtual unsigned int getComponentId() const { return 0; }

		void setOwnerEntity(Entity* entity) { owner = entity; }
		Entity* getOwnerEntity() { return owner; }
	};
}