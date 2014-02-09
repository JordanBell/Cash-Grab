#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::incCycle(void)
{
	cycle = (cycle == 2) ? 0 : cycle+1;
}
