#include "Sinkhole.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

#define POS 1.5*screen->w-4*TILE_SIZE, -screen->h

Sinkhole::Sinkhole(void)
	: GameObject(POS)
{
	m_imageSurface = g_resources->GetSinkholeSheet();
    
    // Add walls along its width
	for (int _x = x+TILE_SIZE/2; _x < x + m_imageSurface->w-TILE_SIZE/2; _x += TILE_SIZE)
		g_game->addCollidable(new Wall(_x, y+m_imageSurface->h-TILE_SIZE));

	m_renderPriority = LAYER_ENV_UPPER;
}

#undef POS
