#include "EnvironmentUpper.h"
#include "Game.h"

EnvironmentUpper* g_environmentUpper = nullptr;

void EnvironmentUpper::render()
{
	int roomOffset = -screen->h;

	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// The door passage columns
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*5) || (_x == TILE_SIZE*14) || (_x == TILE_SIZE*15))
		{
			apply_surface(_x, 0*TILE_SIZE, sprite_sheet, screen, rect_wallTop); // Top WallTop
			apply_surface(_x, 1*TILE_SIZE, sprite_sheet, screen, rect_wall); // Top Wall
			apply_surface(_x, 2*TILE_SIZE, sprite_sheet, screen, rect_wall); // Mid Wall

			//apply_surface(_x, -1*TILE_SIZE, sprite_sheet, screen, rect_wall); // Top Screen's WallTop
		}
		else
		{
			apply_surface(_x, -1*TILE_SIZE, sprite_sheet, screen, rect_wallTop); // Top Screen's WallTop
		}

		// Bottom overhang
		apply_surface(_x, (screen->h - 2*TILE_SIZE), sprite_sheet, screen, rect_wallTop);

		// Left side of door
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14)) {
			apply_surface(_x, -1*TILE_SIZE, sprite_sheet, screen, rect_wallTopOpen_Left); // Top Screen's WallTop
		}
		// Right side of door
		if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15)) {
			apply_surface(_x, -1*TILE_SIZE, sprite_sheet, screen, rect_wallTopOpen_Right); // Top Screen's WallTop
		}
	}

	/*if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
	{
		Wall* bottomWall = new Wall(_x, yVal + screen->h - 2*TILE_SIZE, sprite_sheet, rect_wall);
		g_game->addCollidable(bottomWall, true);
	}*/

		// Bottom Room
	// Clocks
	apply_surface(TILE_SIZE*4.5, 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock1); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock2); // Clock above left doorway

		// Top Room
	// Clocks
	apply_surface(TILE_SIZE*4.5, roomOffset + 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock1); // Clock above left doorway
	apply_surface(TILE_SIZE*14.5, roomOffset + 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock2); // Clock above left doorway

	// The tops of each station
	BuildStationRest(TILE_SIZE * 4, roomOffset + TILE_SIZE * 5);
	BuildStationRest(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5);



	// The wall linings for each of the topWall decors
	for (int offset = 0; offset >= roomOffset; offset += roomOffset)
	{
		// Top & Bottom Linings
		for (int i = TILE_SIZE; i < screen->w - TILE_SIZE; i+=TILE_SIZE) {
			apply_surface(i, 0 + offset, sprite_sheet, screen, rect_wallTop_Bottom); 

			if (offset == 0 || !((i == TILE_SIZE*4) || (i == TILE_SIZE*5) || (i == TILE_SIZE*14) || (i == TILE_SIZE*15)))
				apply_surface(i, screen->h-(offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ *TILE_SIZE + offset, sprite_sheet, screen, rect_wallTop_Top); 
		}

		// Left & Right Linings
		for (int j = TILE_SIZE; j < screen->h - TILE_SIZE; j+=TILE_SIZE) {
			if ((j != screen->h - 2*TILE_SIZE) || (offset == roomOffset)) {
				apply_surface(0, j + offset, sprite_sheet, screen, rect_wallTop_Right);
				apply_surface(screen->w - TILE_SIZE, j + offset, sprite_sheet, screen, rect_wallTop_Left); 
			}
		}

		// Corners
		apply_surface(0, offset, sprite_sheet, screen, rect_wallTop_BRCorner); 
		apply_surface(screen->w-TILE_SIZE, offset, sprite_sheet, screen, rect_wallTop_BLCorner); 
		apply_surface(0, screen->h - (offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ * TILE_SIZE+ offset, sprite_sheet, screen, rect_wallTop_TRCorner); 
		apply_surface(screen->w-TILE_SIZE, screen->h - (offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ * TILE_SIZE+ offset, sprite_sheet, screen, rect_wallTop_TLCorner); 

	}

		// The very outer top decors
	for (int j = -screen->h; j < screen->h-TILE_SIZE; j+=TILE_SIZE)
	{
		// Left & Right
		apply_surface(0, j, sprite_sheet, screen, rect_wallTop_Left); 
		apply_surface(screen->w-TILE_SIZE, j, sprite_sheet, screen, rect_wallTop_Right); 
	}
	for (int i = 0; i < screen->w; i+=TILE_SIZE)
	{
		// Top & Bottom
		apply_surface(i, -screen->h, sprite_sheet, screen, rect_wallTop_Top); 
		apply_surface(i, screen->h-2*TILE_SIZE, sprite_sheet, screen, rect_wallTop_Bottom); 
	}

	// Corners
	//apply_surface(0, -screen->h, sprite_sheet, screen, rect_wallTop_TLCorner); 
	//apply_surface(screen->w-TILE_SIZE, -screen->h, sprite_sheet, screen, rect_wallTop_TRCorner); 
	//apply_surface(0, screen->h - (offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ * TILE_SIZE+ offset, sprite_sheet, screen, rect_wallTop_TRCorner); 
	//apply_surface(screen->w-TILE_SIZE, screen->h - (offset == 0? 2:1) /* Hack. Forgiveness, PLEASE */ * TILE_SIZE+ offset, sprite_sheet, screen, rect_wallTop_TLCorner); 
}

void EnvironmentUpper::BuildStationRest(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		apply_surface(i*TILE_SIZE + _x, _y, sprite_sheet, screen, sprites[i+4][0]);
		apply_surface(i*TILE_SIZE + _x, _y+TILE_SIZE, sprite_sheet, screen, sprites[i+4][1]);
	}
}
