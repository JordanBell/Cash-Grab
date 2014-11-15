#include "Entity.h"

void Entity::render()
{
	set_skin();
	apply_surface(x, y, sprite_sheet, screen, skin);    
}

SDL_Rect Entity::GetCenter() 
{ 
	// Skin width and height, depending on whether or not it's
	int skinW, skinH;
	skinW = skin? skin->w : 0;
	skinH = skin? skin->h : 0;

	// The position, held within a rect object
	SDL_Rect pos = {static_cast<Sint16>(x+(skinW/2)), static_cast<Sint16>(y+(skinH/2)), 0, 0};
	return pos; 
}