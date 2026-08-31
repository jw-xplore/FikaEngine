#pragma once
#include <memory>
#include <cstddef>
#include "core/memorymanagement.h"
#include <iostream>
#include <cassert>

namespace FikaECS
{
	class ECSComponent;

	/**
	 * @brief Stores components of one specific types and runs their update.
	 */
	class ComponentUpdater
	{
	protected:
		unsigned int targetComponentId = 0;

	public:
		ComponentUpdater() {}
		virtual ~ComponentUpdater() {}

		virtual void update(float dt) {}
		virtual void addComponent() { }

		unsigned int getTargetComponentId() { return targetComponentId; }
	};
}