#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace FikaECS
{
	class ECSComponent
	{
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
	};
}