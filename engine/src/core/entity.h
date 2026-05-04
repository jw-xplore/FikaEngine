#pragma once
#include <vector>
#include <initializer_list>

struct EntityId
{
	unsigned int id = 0;
};

static unsigned int entityIdToSet = 1;

class Entity
{
private:
	EntityId id;
	void SetUnassignedId();

public:
	Entity();
	~Entity() {}

	EntityId GetId() { return id; }
};