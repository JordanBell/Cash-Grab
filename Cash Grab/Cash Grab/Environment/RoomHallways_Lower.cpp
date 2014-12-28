#include "RoomHallways_Lower.h"
#include "EnvrionmentSheetIndexes.h"
#include <math.h>
#include "Wall.h"

#define HALLWAY_WIDTH (7*TILE_SIZE)
#define HALLWAY_HEIGHT (8*TILE_SIZE)
#define NUM_SNOW 50

RoomHallways_Lower::RoomHallways_Lower(void)
	: Room(0, -2*screen->h, Dimensions(screen->w, screen->h), RoomElement::NORMAL, LAYER_ENV_LOWER), m_SnowPositions()
{
	BuildWallsLeft();
	BuildWallsRight();

	// Initialise the little snow positions
	SDL_Rect crack1 = { 29*TILE_SIZE, TILE_SIZE, TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack2 = { static_cast<Sint16>(29.5*TILE_SIZE), TILE_SIZE, TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack3 = { 29*TILE_SIZE, static_cast<Sint16>(1.5*TILE_SIZE), TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect crack4 = { static_cast<Sint16>(29.5*TILE_SIZE), static_cast<Sint16>(1.5*TILE_SIZE), TILE_SIZE/2, TILE_SIZE/2 };
	SDL_Rect cracks[] = {crack1, crack2, crack3, crack4};

	for (int i = 0; i < NUM_SNOW; i++)
	{
		// Create a random position, and a random corresponding spritesheet index
		m_SnowPositions.push_back(
			pair<Position, SDL_Rect>(
				Position(rand() % (HALLWAY_WIDTH/8) * 8, 
						 rand() % ((HALLWAY_HEIGHT-TILE_SIZE)/8) * 8),
				cracks[rand()%4]
			)
		);
	}
}

void RoomHallways_Lower::BuildWallsLeft(void)
{
	// LEFT side TOP walls
	for (int _x = x+TILE_SIZE; _x < x+HALLWAY_WIDTH; _x += TILE_SIZE)
		g_game->addCollidable(new Wall(_x, y+screen->h - 9*TILE_SIZE));
	
	// LEFT side RIGHT walls
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		g_game->addCollidable(new Wall(x+HALLWAY_WIDTH, _y));

	// LEFT side LEFT walls
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		if ((_y != y+screen->h-6*TILE_SIZE) && (_y != y+screen->h-7*TILE_SIZE))
			g_game->addCollidable(new Wall(x, _y));

	// LEFT side BOTTOM LEFT
	g_game->addCollidable(new Wall(x+3*TILE_SIZE, y+screen->h-1*TILE_SIZE));
	g_game->addCollidable(new Wall(x+6*TILE_SIZE, y+screen->h-1*TILE_SIZE));
	g_game->addCollidable(new Wall(x+3*TILE_SIZE, y+screen->h-2*TILE_SIZE));
	g_game->addCollidable(new Wall(x+6*TILE_SIZE, y+screen->h-2*TILE_SIZE));
	g_game->addCollidable(new Wall(x+2*TILE_SIZE, y+screen->h-4*TILE_SIZE));
	g_game->addCollidable(new Wall(x+2*TILE_SIZE, y+screen->h-3*TILE_SIZE));
	g_game->addCollidable(new Wall(x+1*TILE_SIZE, y+screen->h-4*TILE_SIZE));
}

void RoomHallways_Lower::BuildWallsRight(void)
{
	// RIGHT side TOP walls
	for (int _x = x+screen->w-HALLWAY_WIDTH; _x < x+screen->w; _x += TILE_SIZE)
		g_game->addCollidable(new Wall(_x, y+screen->h - 9*TILE_SIZE));
	
	// RIGHT side LEFT walls
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		g_game->addCollidable(new Wall(x+screen->w-HALLWAY_WIDTH-TILE_SIZE, _y));

	// RIGHT side RIGHT walls
	for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 4*TILE_SIZE; _y < (y + screen->h); _y += TILE_SIZE)
		if ((_y != y+screen->h-6*TILE_SIZE) && (_y != y+screen->h-7*TILE_SIZE))
			g_game->addCollidable(new Wall(x+screen->w-TILE_SIZE, _y));

	// LEFT side BOTTOM LEFT
	g_game->addCollidable(new Wall(x+screen->w-4*TILE_SIZE, y+screen->h-1*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-7*TILE_SIZE, y+screen->h-1*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-4*TILE_SIZE, y+screen->h-2*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-7*TILE_SIZE, y+screen->h-2*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-3*TILE_SIZE, y+screen->h-4*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-3*TILE_SIZE, y+screen->h-3*TILE_SIZE));
	g_game->addCollidable(new Wall(x+screen->w-2*TILE_SIZE, y+screen->h-4*TILE_SIZE));
}


void RoomHallways_Lower::Render(void)
{
	RenderLeft();
	RenderRight();
}

void RoomHallways_Lower::RenderLeft(void)
{
	// Build the Left Hallway as ICE
	RoomElement e = ICE;
	
	// Floor
	for (int _x = x; _x < x + HALLWAY_WIDTH; _x += TILE_SIZE)
	{
		for (int _y = (y + screen->h) - HALLWAY_HEIGHT; _y < (y + screen->h); _y += TILE_SIZE)
		{
			apply_surface(_x, _y, m_imageSurface, screen, tiles[FLOOR][e]);
		}
	}

	// Random snow piles, as generated in the constructor
	int count = 0;
	for (pair<Position, SDL_Rect> pr : m_SnowPositions) {
		count++;

		apply_surface(x + pr.first.x, (y + screen->h) - HALLWAY_HEIGHT + pr.first.y, m_imageSurface, screen, &pr.second);

		// Sometime's there's snow above
		if (count%4 == 0)
			apply_surface(x + pr.first.x + 4, (y + screen->h) - HALLWAY_HEIGHT + 4 + pr.first.y, m_imageSurface, screen, tiles[SNOW_MINI_2][e]);
	}

	// Walls
	apply_surface(x, (y + screen->h) - HALLWAY_HEIGHT - 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][e]);
	apply_surface(x, (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, tiles[WALL][e]);
	apply_surface(x, (y + screen->h) - HALLWAY_HEIGHT, m_imageSurface, screen, tiles[WALL_BASE][e]);

	for (int _x = x+TILE_SIZE; _x < HALLWAY_WIDTH; _x += TILE_SIZE)
	{
		// Base Wall
		apply_surface(_x, (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][e]);

		// Not Bases
		for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 3*TILE_SIZE; _y < (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE; _y += TILE_SIZE)
		{
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL][e]);
		}
	}

	// Snow Piles
	SDL_Rect snowPileCornerRight = RECT_DEF_SNOW_CORNER_LARGE_RIGHT;
	SDL_Rect snowPileCornerLeft = RECT_DEF_SNOW_CORNER_SMALL_LEFT;
	apply_surface(TILE_SIZE, y + screen->h - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, &snowPileCornerLeft);
	apply_surface(HALLWAY_WIDTH - TILE_SIZE, y + screen->h - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, &snowPileCornerRight);
	
	apply_surface(2 * TILE_SIZE, y + screen->h - 7.85*TILE_SIZE, m_imageSurface, screen, tiles[SNOW_PILE_1][e]);
	apply_surface(4.2 * TILE_SIZE, y + screen->h - 7.3*TILE_SIZE, m_imageSurface, screen, tiles[SNOW_PILE_2][e]);
}

void RoomHallways_Lower::RenderRight(void)
{
	// Build the Right Hallway as FIRE
	RoomElement e = FIRE;
	
	// Floor
	for (int _x = x+screen->w - HALLWAY_WIDTH; _x < x + screen->w; _x += TILE_SIZE)
	{
		for (int _y = (y + screen->h) - HALLWAY_HEIGHT; _y < (y + screen->h); _y += TILE_SIZE)
		{
			apply_surface(_x, _y, m_imageSurface, screen, tiles[FLOOR][e]);
		}
	}

	// Walls
	apply_surface(x+screen->w - TILE_SIZE, (y + screen->h) - HALLWAY_HEIGHT - 2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][e]);
	apply_surface(x+screen->w - TILE_SIZE, (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, tiles[WALL][e]);
	apply_surface(x+screen->w - TILE_SIZE, (y + screen->h) - HALLWAY_HEIGHT, m_imageSurface, screen, tiles[WALL_BASE][e]);

	for (int _x = x+screen->w - HALLWAY_WIDTH; _x < x+screen->w - TILE_SIZE; _x += TILE_SIZE)
	{
		// Base Wall
		apply_surface(_x, (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][e]);

		// Not Bases
		for (int _y = (y + screen->h) - HALLWAY_HEIGHT - 3*TILE_SIZE; _y < (y + screen->h) - HALLWAY_HEIGHT - TILE_SIZE; _y += TILE_SIZE)
		{
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL][e]);
		}
	}
}
