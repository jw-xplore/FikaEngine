#pragma once
#include <memory>
#include "core/memorymanagement.h"

namespace FikaECS
{
	class ECSComponent;

	class SystemBase
	{
	private:
		unsigned int targetComponentId = 0;
		//std::unique_ptr<ECSComponent> components;

	public:
		SystemBase() {}
		SystemBase(unsigned int componentId);

		void update(float dt);
		ECSComponent* addComponent();

		unsigned int getTargetComponentId() const { return targetComponentId; }
	};
}