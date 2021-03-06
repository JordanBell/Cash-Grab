#include "RoomHub_Upper.h"
#include "EnvironmentSheetIndexes.h"

void RoomHub_Upper::Render(void)
{
	// The tops of each station
	RenderStationUpper(TILE_SIZE * 8, TILE_SIZE * 5);

	// Top Walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE)
	{
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*5) || (_x == TILE_SIZE*14) || (_x == TILE_SIZE*15))
		{
			apply_surface(_x, 0*TILE_SIZE - screen->h, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]); // Top WallTop
			apply_surface(_x, 1*TILE_SIZE - screen->h, m_imageSurface, screen, tiles[WALL][m_BaseE]); // Top Wall
			apply_surface(_x, 2*TILE_SIZE - screen->h, m_imageSurface, screen, tiles[WALL][m_BaseE]); // Mid Wall

			// Door Openings
			if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14))
				apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_LEFT][m_BaseE]); // Top Screen's WallTop
			else if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15))
				apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP_OPEN_RIGHT][m_BaseE]); // Top Screen's WallTop
		}
		else if ((_x != 0) && (_x != screen->w-TILE_SIZE)){
			// Bottom walls
			apply_surface(_x, y + (screen->h - TILE_SIZE), m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
		}
	}

	// Clocks
	apply_surface(TILE_SIZE*4.5, y + 1.5*TILE_SIZE, m_imageSurface, screen, tiles[CLOCK_1][ELEMENT_ICE]); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, y + 1.5*TILE_SIZE, m_imageSurface, screen, tiles[CLOCK_2][ELEMENT_FIRE]); // Clock above left doorway

	// The wall linings for each of the topWall decors
	// Top & Bottom Linings
	for (int i = TILE_SIZE; i < screen->w - TILE_SIZE; i+=TILE_SIZE) {
		apply_surface(i, y, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][m_BaseE]); 

		if (!((i == TILE_SIZE*4) || (i == TILE_SIZE*5) || (i == TILE_SIZE*14) || (i == TILE_SIZE*15)))
			apply_surface(i, y + screen->h-TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][m_BaseE]); 
	}

	// Left & Right Linings
	for (int j = TILE_SIZE; j < screen->h - TILE_SIZE; j+=TILE_SIZE) {
		apply_surface(0, y + j, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][m_BaseE]);
		apply_surface(screen->w - TILE_SIZE, y + j, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][m_BaseE]); 
	}

	// Corners
	apply_surface(0, y, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][m_BaseE]); 
	apply_surface(screen->w-TILE_SIZE, y, m_imageSurface, screen, tiles[WALL_TOPBORDER_BL][m_BaseE]); 
	apply_surface(0, y + screen->h - TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][m_BaseE]); 
	apply_surface(screen->w-TILE_SIZE, y + screen->h - TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TL][m_BaseE]);

	// Left & Right outer edge decors
	for (int j = y; j < y+screen->h; j+=TILE_SIZE)
	{
		apply_surface(0, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][m_BaseE]); 
		apply_surface(screen->w-TILE_SIZE, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][m_BaseE]); 
	}
}
