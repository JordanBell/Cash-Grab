#include "Environment.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

Environment* g_environment = nullptr;

Environment::Environment(int x, int y) : GameObject(x, y)
{
	m_imageSurface = g_resources->GetEnvironmentImage();

	//Set the bounds for the clips from the m_imageSurface
	for (int i = 0; i < SHEET_WIDTH; i++)
	{
		for (int j = 0; j < SHEET_HEIGHT; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = TILE_SIZE * i;
			clip->y = TILE_SIZE * j;
			clip->w = clip->h = TILE_SIZE;

			// Add this to the sprites
			sprites[i][j] = clip;
		}
	}
	
	//Define the positions of used components from the m_imageSurface
	rect_floorBrown = sprites[1][0];
	rect_floor = sprites[2][0];
	rect_wallDoor_Left = sprites[0][1];
	rect_wallDoor_Right = sprites[1][1];
	rect_wallTopOpen_Left = sprites[2][1];
	rect_wallTopOpen_Right = sprites[3][1];
	rect_wallDoorShadow = sprites[1][3];
	rect_wallBottom = sprites[0][3];
	rect_clock1 = sprites[0][2];
	rect_clock2 = sprites[1][2];
	rect_paper1 = sprites[2][2];
	rect_paper2 = sprites[3][2];
	
	rect_wallTop = sprites[3][0];
	rect_wallTop_BRCorner = sprites[1][3];
	rect_wallTop_Bottom = sprites[2][3];
	rect_wallTop_BLCorner = sprites[3][3];
	rect_wallTop_Right = sprites[1][4];
	rect_wall = sprites[2][4];
	rect_wallTop_Left = sprites[3][4];
	rect_wallTop_TRCorner = sprites[1][5];
	rect_wallTop_Top = sprites[2][5];
	rect_wallTop_TLCorner = sprites[3][5];

	BuildWalls();

	m_renderPriority = LAYER_ENV_LOWER;
}
	
void Environment::BuildWalls(void)
{
	//Build the walls
	// Left and Right Walls (Bottom)
	for (int _y = 0; _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y, m_imageSurface, rect_wallTop);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y, m_imageSurface, rect_wallTop);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}

	// Left and Right Walls (Top)
	int yVal; // Change based on which part of the map is being built (top or bottom)
	yVal = -screen->h;
	for (int _y = TILE_SIZE; _y < (screen->h); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, yVal + _y, m_imageSurface, rect_wallTop);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, yVal + _y, m_imageSurface, rect_wallTop);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}

	// Top and Bottom Walls (Bottom)
	yVal = 0;
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			// Initialise Top and Bottom
			Wall* topWallTop = new Wall(_x, yVal, m_imageSurface, rect_wallTop);
			Wall* topWall0 = new Wall(_x, yVal + (1*TILE_SIZE), m_imageSurface, rect_wall);
			Wall* topWall1 = new Wall(_x, yVal + (2*TILE_SIZE), m_imageSurface, rect_wall);

			// Make them into collidables
			g_game->addCollidable(topWallTop, true);
			g_game->addCollidable(topWall0, true);
			g_game->addCollidable(topWall1, true);
		}
		
		// Add the bottom wall no matter what
		Wall* bottomWall = new Wall(_x, (screen->h - TILE_SIZE), m_imageSurface, rect_wall);
		g_game->addCollidable(bottomWall, true);
	}
	
	// Top and Bottom Walls (Top)
	yVal = -screen->h;
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Initialise Top and Bottom
		Wall* topWallTop = new Wall(_x, yVal, m_imageSurface, rect_wallTop);
		Wall* topWall0 = new Wall(_x, yVal + (1*TILE_SIZE), m_imageSurface, rect_wall);
		Wall* topWall1 = new Wall(_x, yVal + (2*TILE_SIZE), m_imageSurface, rect_wall);

		// Make them into collidables
		g_game->addCollidable(topWallTop, true);
		g_game->addCollidable(topWall0, true);
		g_game->addCollidable(topWall1, true);
		
		/*if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
		{
			Wall* bottomWall = new Wall(_x, yVal + screen->h - TILE_SIZE, m_imageSurface, rect_wall);
			g_game->addCollidable(bottomWall, true);
		}*/
	}

	// Top Room's item stations
	BuildStationWalls(TILE_SIZE * 4, TILE_SIZE * 5 - screen->h);
	BuildStationWalls(TILE_SIZE * 12, TILE_SIZE * 5 - screen->h);

	// Left and Right Walls
	for (int _y = (TILE_SIZE*4); _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y, m_imageSurface, rect_wallTop);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y, m_imageSurface, rect_wallTop);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}
}

Environment::~Environment()
{
    for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			delete sprites[i][j];
    
    delete rect_floor;
    delete rect_wall;
    delete rect_wallBottom;
	delete rect_wallDoor_Left;
	delete rect_wallDoor_Right;
    delete rect_wallTop;
    delete rect_wallTopOpen_Left;
    delete rect_wallTopOpen_Right;
	delete rect_floorBrown;
	delete rect_clock1;
	delete rect_clock2;
	delete rect_paper1;
	delete rect_paper2;
}

void Environment::BuildStationWalls(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		int j = 2;
		Wall* bottomWall = new Wall(i*TILE_SIZE + _x, j*TILE_SIZE + _y, m_imageSurface, sprites[i+4][j]);
		g_game->addCollidable(bottomWall, true);
	}
}

void Environment::BuildStationRest(const int _x, const int _y)
{
	for (int i = 0; i < 4; i++)
	{
		apply_surface(i*TILE_SIZE + _x, 3*TILE_SIZE + _y, m_imageSurface, screen, sprites[i+4][3]);
	}
}


void Environment::Render(void) 
{
	//Build the floor
	for (int i = 0; i < screen->w; i += TILE_SIZE)
		for (int j = -screen->h; j < screen->h; j += TILE_SIZE)
			apply_surface(i, j, m_imageSurface, screen, rect_floor);

	// LEFT Brown floor coin
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);

	// RIGHT Brown floor coin
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);



	int roomOffset = -screen->h;
	//apply_surface(TILE_SIZE * 2, yVal +  * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 3, roomOffset + TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, roomOffset + TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, roomOffset + TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, roomOffset + TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 2, roomOffset + TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, roomOffset + TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 8, roomOffset + TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 8, roomOffset + TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 8, roomOffset + TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 8, roomOffset + TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);

	// RIGHT Brown floor coin
	//apply_surface(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 11, roomOffset + TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 11, roomOffset + TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 11, roomOffset + TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 11, roomOffset + TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 12, roomOffset + TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, roomOffset + TILE_SIZE * 11, m_imageSurface, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 16, roomOffset + TILE_SIZE * 6, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, roomOffset + TILE_SIZE * 7, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, roomOffset + TILE_SIZE * 8, m_imageSurface, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, roomOffset + TILE_SIZE * 9, m_imageSurface, screen, rect_floorBrown);

	// Station Sections that the player can walk through
	BuildStationRest(TILE_SIZE * 4, roomOffset + TILE_SIZE * 5);
	BuildStationRest(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5);

	// Walls that aren't walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Sometimes the bottom of a wall, sometimes a door. Door is on upper layers, so leave room.
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*5) && (_x != TILE_SIZE*14) && (_x != TILE_SIZE*15))
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, rect_wallBottom); // Bottom Wall, Bottom Room
		
		// Bottom Wall, Top room
		apply_surface(_x, 3*TILE_SIZE - screen->h, m_imageSurface, screen, rect_wallBottom); 

		// Left side of door
		if ((_x == TILE_SIZE*4) || (_x == TILE_SIZE*14)) {
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, rect_wallDoor_Left); // Door
		}
		// Right side of door
		if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*15)) {
			apply_surface(_x, 3*TILE_SIZE, m_imageSurface, screen, rect_wallDoor_Right); // Door
		}
	}

		// Bottom Room	
	// Papers
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 12, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 6, m_imageSurface, screen, rect_paper2);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 10, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 9, TILE_SIZE * 9, m_imageSurface, screen, rect_paper2);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 18, TILE_SIZE * 7, m_imageSurface, screen, rect_paper2);

		// Top Room	
	// Papers
	apply_surface(TILE_SIZE * 3, roomOffset + TILE_SIZE * 12, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 4, roomOffset + TILE_SIZE * 6, m_imageSurface, screen, rect_paper2);
	apply_surface(TILE_SIZE * 14, roomOffset + TILE_SIZE * 10, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 9, roomOffset + TILE_SIZE * 9, m_imageSurface, screen, rect_paper2);
	apply_surface(TILE_SIZE * 12, roomOffset + TILE_SIZE * 5, m_imageSurface, screen, rect_paper1);
	apply_surface(TILE_SIZE * 18, roomOffset + TILE_SIZE * 7, m_imageSurface, screen, rect_paper2);
}
