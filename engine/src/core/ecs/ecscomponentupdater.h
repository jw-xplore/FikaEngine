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

		/*
		ComponentUpdater(unsigned int componentId)
		{
			if (componentId == 0)
				std::cout << "Component id 0 is invalid. Use component id to create matching system. \n";

			assert(componentId != 0);

			// Setup
			targetComponentId = componentId;
			start();
		}
		*/

		virtual void init() {}
		virtual void update(float dt) {}
		virtual void addComponent() { }

		unsigned int getTargetComponentId() { return targetComponentId; }
	};
}