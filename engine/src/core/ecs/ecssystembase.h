#include <memory>
#include "core/memorymanagement.h"

namespace FikaECS
{
	class Component;

	class SystemBase
	{
	private:
		std::unique_ptr<PoolAllocator<Component>> components;

	public:
		void update(float dt);
		Component* addComponent();

		virtual size_t componentID() const { return 0; }
	};
}