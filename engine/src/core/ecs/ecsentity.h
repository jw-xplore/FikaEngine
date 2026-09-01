#pragma once

namespace FikaECS
{
	static unsigned int lastEntityId = 0;

	class Entity
	{
	private:
		unsigned int id = 0;
		void setId(unsigned int id);

	public:
		Entity();
		~Entity() {}
		unsigned int getId() const { return id; }
	};
}