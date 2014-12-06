#include "EnvironmentUpper.h"
#include "EnvrionmentSheetIndexes.h"
#include "Game.h"

EnvironmentUpper* g_environmentUpper = nullptr;

void EnvironmentUpper::Render()
{
	const int e = ELEMENT_NORMAL;
	int roomOffset = -screen->h;

	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// The door passage columns
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*5) || (_x == TILE_SIZE*14) || (_x == TILE_SIZE*15))
		{
			apply_surface(_x, 0*TILE_SIZE, m_imageSurface, screen, sprites[WALL_TOP][e]); // Top WallTop
			apply_surface(_x, 1*TILE_SIZE, m_imageSurface, screen, sprites[WALL][e]); // Top Wall
			apply_surface(_x, 2*TILE_SIZE, m_imageSurface, screen, sprites[WALL][e]); // Mid Wall

			//apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, rect_wall); // Top Screen's WallTop
		}
		else
		{
			apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, sprites[WALL_TOP][e]); // Top Screen's WallTop
		}

		// Bottom overhang
		apply_surface(_x, (screen->h - 2*TILE_SIZE), m_imageSurface, screen, sprites[WALL_TOP][e]);

		// Left side of door
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14)) {
			apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, sprites[WALL_TOP_OPEN_LEFT][e]); // Top Screen's WallTop
		}
		// Right side of door
		if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15)) {
			apply_surface(_x, -1*TILE_SIZE, m_imageSurface, screen, sprites[WALL_TOP_OPEN_RIGHT][e]); // Top Screen's WallTop
		}
	}

		// Bottom Room
	// Clocks
	apply_surface(TILE_SIZE*4.5, 1.5*TILE_SIZE, m_imageSurface, screen, sprites[CLOCK_1][e]); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, 1.5*TILE_SIZE, m_imageSurface, screen, sprites[CLOCK_1][e]); // Clock above left doorway

		// Top Room
	// Clocks
	apply_surface(TILE_SIZE*4.5, roomOffset + 1.5*TILE_SIZE, m_imageSurface, screen, sprites[CLOCK_1][e]); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, roomOffset + 1.5*TILE_SIZE, m_imageSurface, screen, sprites[CLOCK_2][e]); // Clock above left doorway

	// The tops of each station
	BuildStationRest(TILE_SIZE * 4, roomOffset + TILE_SIZE * 5);
	BuildStationRest(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5);



	// The wall linings for each of the topWall decors
	for (int offset = 0; offset >= roomOffset; offset += roomOffset)
	{
		// Top & Bottom Linings
		for (int i = TILE_SIZE; i < screen->w - TILE_SIZE; i+=TILE_SIZE) {
			apply_surface(i, 0 + offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_B][e]); 

			if (offset == 0 || !((i == TILE_SIZE*4) || (i == TILE_SIZE*5) || (i == TILE_SIZE*14) || (i == TILE_SIZE*15)))
				apply_surface(i, screen->h-(offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ *TILE_SIZE + offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_T][e]); 
		}

		// Left & Right Linings
		for (int j = TILE_SIZE; j < screen->h - TILE_SIZE; j+=TILE_SIZE) {
			if ((j != screen->h - 2*TILE_SIZE) || (offset == roomOffset)) {
				apply_surface(0, j + offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_R][e]);
				apply_surface(screen->w - TILE_SIZE, j + offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_L][e]); 
			}
		}

		// Corners
		apply_surface(0, offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_BR][e]); 
		apply_surface(screen->w-TILE_SIZE, offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_BL][e]); 
		apply_surface(0, screen->h - (offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ * TILE_SIZE+ offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_TR][e]); 
		apply_surface(screen->w-TILE_SIZE, screen->h - (offset == 0? 2:1) /* Hack again. */ * TILE_SIZE+ offset, m_imageSurface, screen, sprites[WALL_TOPBORDER_TL][e]); 

	}

		// The very outer top decors
	for (int j = -screen->h; j < screen->h-TILE_SIZE; j+=TILE_SIZE)
	{
		// Left & Right
		apply_surface(0, j, m_imageSurface, screen, sprites[WALL_TOPBORDER_L][e]); 
		apply_surface(screen->w-TILE_SIZE, j, m_imageSurface, screen, sprites[WALL_TOPBORDER_R][e]); 
	}
	for (int i = 0; i < screen->w; i+=TILE_SIZE)
	{
		// Top & Bottom
		apply_surface(i, -screen->h, m_imageSurface, screen, sprites[WALL_TOPBORDER_T][e]); 
		apply_surface(i, screen->h-2*TILE_SIZE, m_imageSurface, screen, sprites[WALL_TOPBORDER_B][e]); 
	}
}

void EnvironmentUpper::BuildStationRest(const int _x, const int _y)
{
	apply_surface(TILE_SIZE + _x, _y, m_imageSurface, screen, sprites[0][VENDOR_MACHINE]);
	apply_surface(2*TILE_SIZE + _x, _y, m_imageSurface, screen, sprites[1][VENDOR_MACHINE]);
	
	for (int i = 0; i < 4; i++)
		apply_surface(i*TILE_SIZE + _x, _y+TILE_SIZE, m_imageSurface, screen, sprites[i+2][VENDOR_MACHINE]);
}
