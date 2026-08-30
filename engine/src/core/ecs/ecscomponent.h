#include <iostream>
#include <string>
#include <memory>

namespace FikaECS
{
	class SystemBase;

	class Component
	{
	private:
		static SystemBase* managerSystem;

	public:
		Component() {}
		virtual ~Component() {}

		/**
		 * @brief Called when Component is added.
		 */
		virtual void start() {}

		/**
		 * @brief Called each frame.
		 * @param dt
		 */
		virtual void update(float dt) {}

		virtual size_t componentID() const { return 0; }
	};
}