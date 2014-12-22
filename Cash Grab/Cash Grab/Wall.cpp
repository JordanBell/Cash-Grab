#include "Wall.h"

#define SHOW_WALLS false

void Wall::Render(void) 
{ 
	if ( SHOW_WALLS ) 
	{ 
		SDL_Rect r = { (Sint16)(x+s_renderingOffset_x), (Sint16)(y+s_renderingOffset_y), 32, 32};
		SDL_FillRect(screen, &r, 0xFF0000FF); 
	} 
}