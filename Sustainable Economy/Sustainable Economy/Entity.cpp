#include "Entity.h"

void Entity::render()
{
	set_skin();
	apply_surface(x, y, sprite_sheet, screen, skin);    
}