#include "Wall.h"
#include "Game.h"

#define SHOW_WALLS false

Wall::Wall(const int x, const int y) 
	: Collidable(x, y), GameObject(x, y)
{ 
	m_IsMoveable = false; 
	m_renderPriority = LAYER_UI-1; 
}

Wall::Wall(const int x, const int y, const int w, const int h) 
	: Collidable(x, y), GameObject(x, y)
{ 
	m_IsMoveable = false; 
	m_renderPriority = LAYER_UI-1; 

	// Set the hitbox w and height
	m_HitBox->w = w;
	m_HitBox->h = h;
}

void Wall::Render(void) 
{ 
	if ( SHOW_WALLS ) 
	{ 
		SDL_Rect r = { (Sint16)(x+cameraRenderingOffset.x), (Sint16)(y+cameraRenderingOffset.y), m_HitBox->w, m_HitBox->h};
		SDL_FillRect(screen, &r, 0x000000FF); 
	} 
}