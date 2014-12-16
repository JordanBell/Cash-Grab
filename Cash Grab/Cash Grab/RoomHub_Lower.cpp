#include "RoomHub_Lower.h"
#include "EnvrionmentSheetIndexes.h"
#include "Wall.h"

RoomHub_Lower::RoomHub_Lower(void)
		: Room(0, -screen->h, Dimensions(screen->w, screen->h), RoomElement::NORMAL, LAYER_ENV_LOWER)
{
	// Left and Right Walls (Top)
	for (int _y = TILE_SIZE; _y < (screen->h); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, y + _y);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, y + _y);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}
	
	// Top and Bottom Walls (Top)
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			// Initialise Top and Bottom
			Wall* topWallTop = new Wall(_x, y);
			Wall* topWall0 = new Wall(_x, y + (1*TILE_SIZE));
			Wall* topWall1 = new Wall(_x, y + (2*TILE_SIZE));

			// Make them into collidables
			g_game->addCollidable(topWallTop, true);
			g_game->addCollidable(topWall0, true);
			g_game->addCollidable(topWall1, true);
		}

		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
			g_game->addCollidable(new Wall(_x, y+screen->h-TILE_SIZE));

		// Add the bottom wall no matter what
		//apply_surface(_x, y + (screen->h - TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
	}

	// Room's item station walls
	CreateStationWalls(TILE_SIZE * 4, TILE_SIZE * 5);
	CreateStationWalls(TILE_SIZE * 12, TILE_SIZE * 5);
}

void RoomHub_Lower::Render(void)
{
	//Build the floor
	for (int i = 0; i < screen->w; i += TILE_SIZE)
		for (int j = 0; j < screen->h; j += TILE_SIZE)
			apply_surface(i, y + j, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);

	//apply_surface(x + TILE_SIZE * 2, yVal +  * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 4, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 5, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 6, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 3, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 3, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 3, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 3, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	//apply_surface(x + TILE_SIZE * 2, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 4, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 5, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 6, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

	// RIGHT Brown floor coin
	//apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 13, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 14, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 15, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 17, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	//apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 13, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 14, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 15, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 17, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

	// Papers
	apply_surface(x + TILE_SIZE * 3, y + TILE_SIZE * 12, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(x + TILE_SIZE * 4, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);
	apply_surface(x + TILE_SIZE * 14, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(x + TILE_SIZE * 9, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(x + TILE_SIZE * 18, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);
	
	// Top and Bottom Walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		apply_surface(_x, y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
		apply_surface(_x, y + (1*TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y + (2*TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y + (3*TILE_SIZE), m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

		/*if ((_x != TILE_SIZE*5) && (_x != TILE_SIZE*4) && (_x != TILE_SIZE*15) && (_x != TILE_SIZE*14))
			apply_surface(_x, 3*TILE_SIZE - screen->h, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);*/

		if (_x == TILE_SIZE*4)
				apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LOCKED_LEFT][ELEMENT_ICE]); // Door
		if (_x == TILE_SIZE*5)
				apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LOCKED_RIGHT][ELEMENT_ICE]); // Door
		if (_x == TILE_SIZE*14)
				apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LOCKED_LEFT][ELEMENT_FIRE]); // Door
		if (_x == TILE_SIZE*15)
				apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LOCKED_RIGHT][ELEMENT_FIRE]); // Door

		// Add the bottom wall no matter what
		apply_surface(_x, y + (screen->h - TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
	}

	// Left and Right Walls
	for (int _y = TILE_SIZE; _y < (screen->h); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
		apply_surface(0, y + _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
        apply_surface(screen->w - TILE_SIZE, y + _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	}

	// Room's item station walls
	RenderStationWalls(TILE_SIZE * 4, TILE_SIZE * 5);
	RenderStationWalls(TILE_SIZE * 12, TILE_SIZE * 5);
	RenderStation(TILE_SIZE * 4, TILE_SIZE * 6);
	RenderStation(TILE_SIZE * 12, TILE_SIZE * 6);
}


void RoomHub_Lower::CreateStationWalls(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		int j = 2;
		Wall* bottomWall = new Wall(x + i*TILE_SIZE + _x, y + j*TILE_SIZE + _y);
		g_game->addCollidable(bottomWall, true);
	}
}

void RoomHub_Lower::RenderStationWalls(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		int j = 2;
		apply_surface(x + i*TILE_SIZE + _x, y + j*TILE_SIZE + _y, m_imageSurface, screen, tiles[i+(j*4)-2][VENDOR_MACHINE]);
	}
}

void RoomHub_Lower::RenderStation(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++) {
		apply_surface(x + i*TILE_SIZE + _x, y + 2*TILE_SIZE + _y, m_imageSurface, screen, tiles[i+(2*4)+2][VENDOR_MACHINE]);
	}
}