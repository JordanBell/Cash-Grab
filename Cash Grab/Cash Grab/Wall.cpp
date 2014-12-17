#include "Wall.h"

#define SHOW_WALLS false

void Wall::Render(void) 
{ 
	if ( SHOW_WALLS ) 
	{ 
		SDL_Rect r = {x+s_renderingOffset_x, y+s_renderingOffset_y, 32, 32}; 
		SDL_FillRect(screen, &r, 0xFF0000FF); 
	} 
}