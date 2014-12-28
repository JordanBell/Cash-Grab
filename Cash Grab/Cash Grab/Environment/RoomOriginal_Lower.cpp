#include "RoomOriginal_Lower.h"
#include "Game.h"
#include "EnvrionmentSheetIndexes.h"
#include "Wall.h"
#include "Wallet.h"
#include "InteractZone.h"
#include "UI.h"

RoomOriginal_Lower::RoomOriginal_Lower(void)
		: Room(0, 0, Dimensions(screen->w, screen->h), RoomElement::NORMAL, LAYER_ENV_LOWER) 
{
	// Initialise the dispenser
	Machine* machine = new Machine(x + (7*TILE_SIZE), y + (TILE_SIZE));
	SDL_Rect* zoneRect = new SDL_Rect();
	zoneRect->x = machine->x;
	zoneRect->y = machine->y + 3*TILE_SIZE;
	zoneRect->w = 6*TILE_SIZE;
	zoneRect->h = TILE_SIZE/2;

	InteractZone* machineActivation = new InteractZone(zoneRect, [machine] { machine->Dispense();}, Player::Direction::UP);

	SetMachine(machine);
	g_game->addCollidable(machine);

	// Create a prompt, linking to that machine TODO: Link it to the wallet instead.
	//g_game->addGameObject(new Prompt(machine));

	// Build the walls
	// Left and Right Walls (Bottom)
	for (int _y = 0; _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}

	// Top and Bottom Walls (Bottom)
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			// Initialise Top and Bottom
			Wall* topWallTop = new Wall(_x, 0);
			Wall* topWall0 = new Wall(_x, 0 + (1*TILE_SIZE));
			Wall* topWall1 = new Wall(_x, 0 + (2*TILE_SIZE));
			Wall* topWall2 = new Wall(_x, 0 + (3*TILE_SIZE));

			// Make them into collidables
			g_game->addCollidable(topWallTop, true);
			g_game->addCollidable(topWall0, true);
			g_game->addCollidable(topWall1, true);
			g_game->addCollidable(topWall2, true);
		}
		
		// Add the bottom wall no matter what
		Wall* bottomWall = new Wall(_x, (screen->h - TILE_SIZE));
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
}

void RoomOriginal_Lower::Update(int delta)
{
	// Update the room machine's GUI
	g_UI->SetCollectedCoins(Wallet::GetCoins());
    g_UI->SetRequiredCoins(GetMachine()->coinCost);
    g_UI->SetTotalCoins(Wallet::GetTotalCoins());
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
		// Sometimes the bottom of a wall, sometimes a door. Door is on upper layers, so leave room.
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]); // Bottom Wall, Bottom Room

		// Left side of BOTTOM ROOM door
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14))
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[DOOR_LEFT][m_BaseE]); // Door
		
		// Right side of BOTTOM ROOM door
		if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15))
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, tiles[DOOR_RIGHT][m_BaseE]); // Door
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
