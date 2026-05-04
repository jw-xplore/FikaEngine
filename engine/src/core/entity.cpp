#include "entity.h"

Entity::Entity()
{
	SetUnassignedId();
}

void Entity::SetUnassignedId()
{
	if (this->id.id != 0)
		return;

	this->id.id = entityIdToSet;
	entityIdToSet++;
}