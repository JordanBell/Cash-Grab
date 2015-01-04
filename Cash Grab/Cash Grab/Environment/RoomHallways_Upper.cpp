#include "RoomHallways_Upper.h"
#include "EnvironmentSheetIndexes.h"

#define HALLWAY_WIDTH (7*TILE_SIZE)
#define HALLWAY_HEIGHT (8*TILE_SIZE)

void RoomHallways_Upper::Render(void)
{
	RenderLeft();
	RenderRight();
}

void RoomHallways_Upper::RenderLeft(void)
{
	Element e = ICE;

	// Top wall WALL_TOP
	for (int _x = x; _x < HALLWAY_WIDTH+TILE_SIZE; _x += TILE_SIZE)
		for (int _y = y; _y < (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE+TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// Right side WALL_TOP
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		apply_surface(x+HALLWAY_WIDTH, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// The Left
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		if (!((_y <= y+screen->h-6*TILE_SIZE) && (_y >= y+screen->h-10*TILE_SIZE)))
			apply_surface(x, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// The Rest
	apply_surface(x+1*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+1*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+1*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+1*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);

	apply_surface(x+2*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+3*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+6*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// Open Tops
	apply_surface(x+3*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	apply_surface(x+4*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_LEFT][e]);
	apply_surface(x+5*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_RIGHT][e]);
	apply_surface(x+6*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TL][e]);
	
	// Wall Linings
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+2*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+1*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	
	apply_surface(x, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);

	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][e]);
	apply_surface(x+7*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TL][e]);

	for (int _y = y+screen->h - HALLWAY_HEIGHT - 3*TILE_SIZE; _y < y+screen->h - 2*TILE_SIZE; _y += TILE_SIZE)
		apply_surface(x+7*TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][e]);

	apply_surface(x+7*TILE_SIZE, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BL][e]);

	for (int _x = x+TILE_SIZE; _x < x+HALLWAY_WIDTH; _x += TILE_SIZE)
		apply_surface(_x, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][e]);
	
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][e]);
}

void RoomHallways_Upper::RenderRight(void)
{
	Element e = FIRE;

	// Top wall WALL_TOP
	for (int _x = x+screen->w-HALLWAY_WIDTH-TILE_SIZE; _x < screen->w; _x += TILE_SIZE)
		for (int _y = y; _y < (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE+TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// Right side WALL_TOP
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		apply_surface(x+screen->w-HALLWAY_WIDTH-TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// The Left
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		if (!((_y <= y+screen->h-6*TILE_SIZE) && (_y >= y+screen->h-10*TILE_SIZE)))
			apply_surface(x+screen->w-TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// The Rest
	apply_surface(x+screen->w-2*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-2*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-2*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);

	apply_surface(x+screen->w-3*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-3*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-3*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	
	apply_surface(x+screen->w-4*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-7*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-4*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);
	apply_surface(x+screen->w-7*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][e]);

	// Open Tops
	apply_surface(x+screen->w-6*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_LEFT][e]);
	apply_surface(x+screen->w-5*TILE_SIZE, y+screen->h-1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_RIGHT][e]);
	
	// Wall Linings
	/*apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+2*TILE_SIZE, y+screen->h-3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+1*TILE_SIZE, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	
	apply_surface(x, y+screen->h-4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);

	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x, y+screen->h-5*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][e]);
	
	apply_surface(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][e]);
	apply_surface(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][e]);
	apply_surface(x+7*TILE_SIZE, y+screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TL][e]);

	for (int _y = y+screen->h - HALLWAY_HEIGHT - 3*TILE_SIZE; _y < y+screen->h - 2*TILE_SIZE; _y += TILE_SIZE)
		apply_surface(x+7*TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][e]);

	apply_surface(x+7*TILE_SIZE, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BL][e]);

	for (int _x = x+TILE_SIZE; _x < x+HALLWAY_WIDTH; _x += TILE_SIZE)
		apply_surface(_x, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][e]);
	
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][e]);
	apply_surface(x, y+screen->h-HALLWAY_HEIGHT - 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][e]);*/
}

