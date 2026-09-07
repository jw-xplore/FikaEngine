#pragma once
#include <string>

struct Prefab;

namespace FikaECS
{
	static unsigned int lastEntityId = 0;

	class Entity
	{
	private:
		unsigned int id = 0;
		std::string name;
		void setId(unsigned int id);
		Prefab* sourcePrefab;

	public:
		Entity();
		Entity(std::string name);
		~Entity() {}

		unsigned int getId() const { return id; }
		void setName(std::string name) { this->name = name; }
		std::string getName() { return name; }
		void setSourcePrefab(Prefab* prefab) { sourcePrefab = prefab; }
		Prefab* getSourcePrefab() { return sourcePrefab; }
	};
}