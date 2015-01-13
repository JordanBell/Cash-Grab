#include "RoomOriginal_Lower.h"
#include "Game.h"
#include "EnvironmentSheetIndexes.h"
#include "Wall.h"
#include "Inventory.h"
#include "InteractZone.h"
#include "UI.h"
#include "Machine.h"
#include "Door.h"

RoomOriginal_Lower::RoomOriginal_Lower(void)
		: Room(0, 0, Dimensions(screen->w, screen->h), Element::NORMAL, LAYER_ENV_LOWER) 
{
	// Initialise the dispenser
	Machine* machine = new Machine(x + (7*TILE_SIZE), y + (TILE_SIZE));
	SDL_Rect* zoneRect = new SDL_Rect();
	zoneRect->x = machine->x;
	zoneRect->y = machine->y + 3*TILE_SIZE;
	zoneRect->w = 6*TILE_SIZE;
	zoneRect->h = TILE_SIZE/2;

	InteractZone* machineActivation = new InteractZone(zoneRect, [machine] { machine->Dispense();}, Player::Direction::UP);

	SetDispenser(machine);
	g_game->addCollidable(machine);

	// Left and Right Walls
	for (int _y = 0; _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
        g_game->addCollidable(new Wall(0, _y));
        g_game->addCollidable(new Wall(screen->w - TILE_SIZE, _y));
	}

	// Top and Bottom Walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			g_game->addCollidable(new Wall(_x, 0));
			g_game->addCollidable(new Wall(_x, 0 + (1*TILE_SIZE)));
			g_game->addCollidable(new Wall(_x, 0 + (2*TILE_SIZE)));
			g_game->addCollidable(new Wall(_x, 0 + (3*TILE_SIZE)));
		}
		
		// Add the bottom wall no matter what
		Wall* bottomWall = new Wall(_x, (screen->h - 2*TILE_SIZE));
		g_game->addCollidable(bottomWall, true);
	}

	// Left and Right Walls
	for (int _y = (TILE_SIZE*4); _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}

	// Add the doors.  Set as initially open if testing, closed in full game.
	g_game->addGameObject(new Door(TILE_SIZE*4, 3*TILE_SIZE, m_BaseE, DOOR_ID_TOHUB, GAME_TYPE == "testing"));
	g_game->addGameObject(new Door(TILE_SIZE*14, 3*TILE_SIZE, m_BaseE, DOOR_ID_TOHUB, GAME_TYPE == "testing"));
}

void RoomOriginal_Lower::Update(int delta)
{
	// Update the room machine's GUI
	g_UI->SetCollectedCoins(Inventory::GetInstance().normCoins->GetAmount());
    g_UI->SetRequiredCoins(GetDispenser()->GetCost());
    g_UI->SetTotalCoins(Inventory::GetInstance().normCoins->GetTotal());
}

void RoomOriginal_Lower::Render(void)
{
	//Build the floor
	for (int i = 0; i < screen->w; i += TILE_SIZE)
		for (int j = 0; j < screen->h; j += TILE_SIZE)
			apply_surface(i, j, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);

	// LEFT Alt floor
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

	// RIGHT alt floor
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 5, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 11, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 6, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 7, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 8, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 9, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 10, m_imageSurface, screen, tiles[FLOOR_ALT][m_BaseE]);

	// Walls that aren't walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Sometimes the bottom of a wall, sometimes a door, so leave room.
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]); // Bottom Wall, Bottom 

		//// Left side of door
		//if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14))
		//	apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[DOOR_LEFT][m_BaseE]); // Door
		//
		//// Right side of door
		//if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15))
		//	apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[DOOR_RIGHT][m_BaseE]); // Door
	}

	// Papers
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 12, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 6, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 10, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(TILE_SIZE * 9, TILE_SIZE * 9, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, m_imageSurface, screen, tiles[PAPER_1][m_BaseE]);
	apply_surface(TILE_SIZE * 18, TILE_SIZE * 7, m_imageSurface, screen, tiles[PAPER_2][m_BaseE]);

	// Build the walls
	// Top and Bottom Walls (Bottom)
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			// Initialise Top and Bottom
			apply_surface(_x, 0, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
			apply_surface(_x, 0 + (1*TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
			apply_surface(_x, 0 + (2*TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
		}
		
		// Add the bottom wall no matter what
		apply_surface(_x, (screen->h - TILE_SIZE), m_imageSurface, screen, tiles[WALL][m_BaseE]);
	}

	// Left and Right Walls
	for (int _y = 0; _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        apply_surface(0, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
        apply_surface(screen->w - TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	}

	// Left and Right Walls
	for (int _y = (TILE_SIZE*4); _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        apply_surface(0, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
        apply_surface(screen->w - TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	}
}
