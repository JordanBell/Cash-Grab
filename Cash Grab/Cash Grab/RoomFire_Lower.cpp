#include "RoomFire_Lower.h"
#include "Wall.h"
#include "EnvrionmentSheetIndexes.h"


RoomFire_Lower::RoomFire_Lower(void)
	: Room(screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), FIRE, LAYER_ENV_LOWER)
{
	// Top Walls
	for (int _x = x+TILE_SIZE; _x < x + m_Size.x; _x += TILE_SIZE) 
	{
		g_game->addCollidable(new Wall(_x, y+m_Size.y-TILE_SIZE));
		g_game->addCollidable(new Wall(_x, y+2*TILE_SIZE));
	}

	// Side Walls
	for (int _y = y; _y < y + m_Size.y; _y += TILE_SIZE)
	{
		// Left Walls
		if ((_y != y+7*TILE_SIZE) && (_y != y+8*TILE_SIZE) && (_y != y+9*TILE_SIZE))
			g_game->addCollidable(new Wall(x, _y));
		
		// Right Walls
		g_game->addCollidable(new Wall(x+screen->w-TILE_SIZE, _y));
	}
}

void RoomFire_Lower::Render(void)
{
	// Floor
	for (int _x = x; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE)
		for (int _y = y+4*TILE_SIZE; _y < y + m_Size.y-TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
	
	// Top Wall
	for (int _x = x; _x < x + screen->w; _x += TILE_SIZE)
		for (int _y = y+4*TILE_SIZE; _y < y-TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

	for (int _x = x+TILE_SIZE; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE) {
		apply_surface(_x, y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
		apply_surface(_x, y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);
	}

	// Left Column
	apply_surface(x, y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+5*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x, y+6*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x, y+7*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

	apply_surface(x, y+8*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
	apply_surface(x, y+9*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
}