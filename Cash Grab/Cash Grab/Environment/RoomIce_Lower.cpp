#include "RoomIce_Lower.h"
#include "EnvrionmentSheetIndexes.h"
#include "Wall.h"

#define NUM_SNOW 300
#define NUM_PILES 0
RoomIce_Lower::RoomIce_Lower(void)
	: Room(-screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), ICE, LAYER_ENV_LOWER)
{
	// Top Walls
	for (int _x = x+TILE_SIZE; _x < x + m_Size.x; _x += TILE_SIZE) 
	{
		g_game->addCollidable(new Wall(_x, y+m_Size.y-TILE_SIZE));
		g_game->addCollidable(new Wall(_x, y+3*TILE_SIZE));
	}

	// Side Walls
	for (int _y = y; _y < y + m_Size.y; _y += TILE_SIZE)
	{
		// Left Walls
		g_game->addCollidable(new Wall(x, _y));

		// Right Walls
		if ((_y != y+8*TILE_SIZE) && (_y != y+9*TILE_SIZE))
			g_game->addCollidable(new Wall(x + screen->w-TILE_SIZE, _y));
	}

	// Random floor decoration
	SDL_Rect crack1 = { 29*TILE_SIZE, TILE_SIZE, TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack2 = { static_cast<Sint16>(29.5*TILE_SIZE), TILE_SIZE, TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack3 = { 29*TILE_SIZE, static_cast<Sint16>(1.5*TILE_SIZE), TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack4 = { static_cast<Sint16>(29.5*TILE_SIZE), static_cast<Sint16>(1.5*TILE_SIZE), TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect cracks[] = {crack1, crack2, crack3, crack4};

	for (int i = 0; i < NUM_SNOW; i++)
	{
		// Create a random position, and a random corresponding spritesheet rect
		m_SnowPositions.push_back(
			pair<Position, SDL_Rect>(
				Position(rand() % (screen->w / 8) * 8, 
						 rand() % ((2*screen->h-5*TILE_SIZE) / 8) * 8 + 4*TILE_SIZE),
				cracks[rand()%4]
			)
		);
	}

	for (int i = 0; i < NUM_PILES; i++)
	{
		// Create a random position, and a random corresponding spritesheet index
		m_SnowPositions_Piles.push_back(
			pair<Position, int>(
				Position(rand() % screen->w, 
						 rand() % (2*screen->h-5*TILE_SIZE) + 4*TILE_SIZE),
				rand() % 2 ? SNOW_PILE_1 : SNOW_PILE_2
			)
		);
	}
}

void RoomIce_Lower::Render(void)
{
	// Floor
	for (int _x = x+TILE_SIZE; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE)
		for (int _y = y+4*TILE_SIZE; _y < y + m_Size.y-TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);

	// Random ice floors, as generated in the constructor
	int count = 0;
	for (pair<Position, SDL_Rect> pr : m_SnowPositions) {
		count++;

		apply_surface(x + pr.first.x, (y + screen->h) - screen->h + pr.first.y, m_imageSurface, screen, &pr.second);

		// Sometime's there's snow above
		if (count%10 == 0)
			apply_surface(x + pr.first.x + 4, (y + screen->h) - screen->h + 4 + pr.first.y, m_imageSurface, screen, tiles[SNOW_MINI_2][m_BaseE]);
	}

	// Random snow piles, as generated in the constructor
	for (pair<Position, int> pr : m_SnowPositions_Piles) 
	{
		apply_surface(x + pr.first.x, 
					  y + pr.first.y, 
					  m_imageSurface, screen, tiles[pr.second][m_BaseE]);
	}
	
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

	// Right Column
	apply_surface(x + screen->w-TILE_SIZE, y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+5*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+6*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+7*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

	apply_surface(x + screen->w-TILE_SIZE, y+8*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
	apply_surface(x + screen->w-TILE_SIZE, y+9*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
}

