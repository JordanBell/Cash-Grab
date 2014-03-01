#include "Entity.h"

SDL_Surface *Entity::sprite_sheet;

void Entity::render()
{
	set_skin();
	apply_surface(x, y, sprite_sheet, screen, skin);    
}