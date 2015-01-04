#include "RoomOriginal_Upper.h"
#include "EnvironmentSheetIndexes.h"


void RoomOriginal_Upper::Render(void)
{
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// The door passage columns
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*5) || (_x == TILE_SIZE*14) || (_x == TILE_SIZE*15))
		{
			apply_surface(_x, 0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]); // Top WallTop
			apply_surface(_x, 1*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]); // Top Wall
			apply_surface(_x, 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]); // Mid Wall

			//apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, rect_wall); // Top Screen's WallTop
		}
		else
		{
			//apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]); // Top Screen's WallTop
		}

		// Bottom overhang
		apply_surface(_x, (screen->h - 2*TILE_SIZE), m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	}

	// Clocks
	apply_surface(TILE_SIZE*4.5, 1.5*TILE_SIZE, m_imageSurface, screen, tiles[CLOCK_2][m_BaseE]); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, 1.5*TILE_SIZE, m_imageSurface, screen, tiles[CLOCK_1][m_BaseE]); // Clock above left doorway
	
	// Top & Bottom Linings
	for (int i = TILE_SIZE; i < screen->w - TILE_SIZE; i+=TILE_SIZE) {
		apply_surface(i, 0, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][m_BaseE]); 
		apply_surface(i, screen->h- 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_T][m_BaseE]); 
	}

	// Left & Right Linings
	for (int j = TILE_SIZE; j < screen->h - TILE_SIZE; j+=TILE_SIZE) {
		if (j != screen->h - 2*TILE_SIZE) {
			apply_surface(0, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][m_BaseE]);
			apply_surface(screen->w - TILE_SIZE, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][m_BaseE]); 
		}
	}

	// Corners
	apply_surface(0, 0, m_imageSurface, screen, tiles[WALL_TOPBORDER_BR][m_BaseE]); 
	apply_surface(screen->w-TILE_SIZE, 0, m_imageSurface, screen, tiles[WALL_TOPBORDER_BL][m_BaseE]); 
	apply_surface(0, screen->h - 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TR][m_BaseE]); 
	apply_surface(screen->w-TILE_SIZE, screen->h - 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_TL][m_BaseE]);

	// The very outer top decors
	for (int j = 0; j < screen->h-TILE_SIZE; j+=TILE_SIZE)
	{
		// Left & Right
		apply_surface(0, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_L][m_BaseE]); 
		apply_surface(screen->w-TILE_SIZE, j, m_imageSurface, screen, tiles[WALL_TOPBORDER_R][m_BaseE]); 
	}
	for (int i = 0; i < screen->w; i+=TILE_SIZE)
	{
		// Bottom 
		apply_surface(i, screen->h-2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOPBORDER_B][m_BaseE]); 
	}
}

