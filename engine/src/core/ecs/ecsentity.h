#pragma once
#include <string>

namespace FikaECS
{
	static unsigned int lastEntityId = 0;

	class Entity
	{
	private:
		unsigned int id = 0;
		std::string name;
		void setId(unsigned int id);

	public:
		Entity();
		Entity(std::string name);
		~Entity() {}

		unsigned int getId() const { return id; }
		void setName(std::string name) { this->name = name; }
		std::string getName() { return name; }
	};
}