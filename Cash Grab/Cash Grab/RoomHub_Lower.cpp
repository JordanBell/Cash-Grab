#include "RoomHub_Lower.h"
#include "EnvironmentSheetIndexes.h"
#include "Wall.h"
#include "Door.h"

RoomHub_Lower::RoomHub_Lower(void)
		: Room(0, -screen->h, Dimensions(screen->w, screen->h), Element::NORMAL, LAYER_ENV_LOWER)
{
	// Left and Right Walls
	for (int _y = TILE_SIZE; _y < (screen->h); _y += TILE_SIZE) // Loop through height
	{
		// Make them into collidables
        g_game->addCollidable(new Wall(0, y + _y));
        g_game->addCollidable(new Wall(screen->w - TILE_SIZE, y + _y));
	}
	
	// Top and Bottom Walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			// Make them into collidables
			g_game->addCollidable(new Wall(_x, y));
			g_game->addCollidable(new Wall(_x, y + (1*TILE_SIZE)));
			g_game->addCollidable(new Wall(_x, y + (2*TILE_SIZE)));
			g_game->addCollidable(new Wall(_x, y + (3*TILE_SIZE)));
		}

		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
			g_game->addCollidable(new Wall(_x, y+screen->h-TILE_SIZE));

		// Add the bottom wall no matter what
		//apply_surface(_x, y + (screen->h - TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
	}

	// Add doors. Set as initially open if testing, closed in full game.
	g_game->addGameObject(new Door(TILE_SIZE*4, 3*TILE_SIZE-screen->h, (Element)ELEMENT_ICE, DOOR_ID_TOICE, GAME_TYPE == "testing"));
	g_game->addGameObject(new Door(TILE_SIZE*14, 3*TILE_SIZE-screen->h, (Element)ELEMENT_FIRE, DOOR_ID_TOFIRE, GAME_TYPE == "testing"));

	// Room's item station walls
	CreateStationWalls(TILE_SIZE * 8, TILE_SIZE * 5);
	// Add its InteractZone
	SDL_Rect* interactArea = new SDL_Rect();
	interactArea->x = x+TILE_SIZE*8;
	interactArea->y = y+TILE_SIZE*9;
	interactArea->w = TILE_SIZE*4;
	interactArea->h = TILE_SIZE/3;
	InteractZone* zone = new InteractZone(interactArea, [] { g_player->Say("It's not working..."); }, Player::Direction::UP);
}

void RoomHub_Lower::Render(void)
{
	//Build the floor
	for (int i = 0; i < screen->w; i += TILE_SIZE)
		for (int j = 0; j < screen->h; j += TILE_SIZE)
			apply_surface(i, y + j, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);

	//apply_surface(x + TILE_SIZE * 2, yVal +  * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 9, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 10, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	//apply_surface(x + TILE_SIZE * 2, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 8, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 9, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 10, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 7, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

	// RIGHT Brown floor coin
	//apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 13, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 14, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 15, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	////apply_surface(x + TILE_SIZE * 17, y + TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//
	//apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 11, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//
	////apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 12, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 13, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 14, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 15, y + TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	////apply_surface(x + TILE_SIZE * 17, y + TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//
	//apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(x + TILE_SIZE * 16, y + TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

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

		//if (_x == TILE_SIZE*4)
		//		apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LEFT][ELEMENT_ICE]); // Door
		//if (_x == TILE_SIZE*5)
		//		apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_RIGHT][ELEMENT_ICE]); // Door
		//if (_x == TILE_SIZE*14)
		//		apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_LEFT][ELEMENT_FIRE]); // Door
		//if (_x == TILE_SIZE*15)
		//		apply_surface(_x, 3*TILE_SIZE-screen->h, m_imageSurface, screen, tiles[DOOR_RIGHT][ELEMENT_FIRE]); // Door
	}

	// Left and Right Walls
	for (int _y = TILE_SIZE; _y < (screen->h); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
		apply_surface(0, y + _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
        apply_surface(screen->w - TILE_SIZE, y + _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	}

	// Room's item station walls
	RenderStationLower(TILE_SIZE * 8, TILE_SIZE * 5);
}