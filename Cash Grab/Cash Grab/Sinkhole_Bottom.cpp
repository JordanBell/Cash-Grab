#include "Sinkhole_Bottom.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

#define POS 1.5*screen->w-4*TILE_SIZE, -screen->h+3*TILE_SIZE

Sinkhole_Bottom::Sinkhole_Bottom(void)
	: GameObject(POS)
{
	m_imageSurface = g_resources->GetSinkholeSheet();

	// Get the bottom rect
	m_imageRect = new SDL_Rect();
	m_imageRect->y = 0.75f*m_imageSurface->h;
	m_imageRect->w = m_imageSurface->w;
	m_imageRect->h = 0.25f*m_imageSurface->h;
    
    // Add walls along its width
	for (int _x = x+TILE_SIZE/2; _x < x + m_imageSurface->w-TILE_SIZE/2; _x += TILE_SIZE)
	{
		g_game->addCollidable(new Wall(_x, y+TILE_SIZE-1.5*TILE_SIZE));
		g_game->addCollidable(new Wall(_x, y+TILE_SIZE-TILE_SIZE));
	}

	m_renderPriority = LAYER_ENV_LOWER;
}

#undef POS
