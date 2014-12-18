#include "Sinkhole_Top.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

#define POS 1.5*screen->w-4*TILE_SIZE, -screen->h

Sinkhole_Top::Sinkhole_Top(void)
	: GameObject(POS)
{
	m_imageSurface = g_resources->GetSinkholeSheet();

	// Get the top rect
	m_imageRect = new SDL_Rect();
	m_imageRect->w = m_imageSurface->w;
	m_imageRect->h = 0.75f*m_imageSurface->h;

	m_renderPriority = LAYER_ENV_UPPER;
}

#undef POS
