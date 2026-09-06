#include "ecsentity.h"
#include <iostream>

namespace FikaECS
{
	Entity::Entity()
	{
		lastEntityId++;
		setId(lastEntityId);
	}

	Entity::Entity(std::string name)
	{
		lastEntityId++;
		setId(lastEntityId);
		this->name = name;
	}

	void Entity::setId(unsigned int id)
	{
		if (id == 0)
		{
			std::cout << "Error: Setting entity id to 0 (" << this->id << ")\n";
			return;
		}

		if (this->id != 0)
		{
			std::cout << "Error: Attempting to set id of existing entity (" << this->id << ")\n";
			return;
		}

		this->id = id;
	}
}