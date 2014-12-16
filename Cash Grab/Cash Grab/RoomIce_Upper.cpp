#include "RoomIce_Upper.h"
#include "EnvrionmentSheetIndexes.h"

void RoomIce_Upper::Render(void)
{
	// Top Walls
	for (int _x = x+TILE_SIZE; _x < x + m_Size.x; _x += TILE_SIZE) 
		apply_surface(_x, y+m_Size.y-TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);

	// Side Walls
	for (int _y = y; _y < y + m_Size.y; _y += TILE_SIZE)
		apply_surface(x, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	for (int _y = y+10*TILE_SIZE; _y < y + m_Size.y; _y += TILE_SIZE)
		apply_surface(x + screen->w-TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);

}
