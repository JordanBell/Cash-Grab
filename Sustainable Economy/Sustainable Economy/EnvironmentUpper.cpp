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
}

void EnvironmentUpper::BuildStationRest(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		apply_surface(i*TILE_SIZE + _x, _y, sprite_sheet, screen, sprites[i+4][0]);
		apply_surface(i*TILE_SIZE + _x, _y+TILE_SIZE, sprite_sheet, screen, sprites[i+4][1]);
	}
}
