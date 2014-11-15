#include "Environment.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

Environment* g_environment = nullptr;

Environment::Environment(int x, int y) : Entity(x, y)
{
	sprite_sheet = g_resources->GetEnvironmentImage();

	//Set the bounds for the clips from the sprite_sheet
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = TILE_SIZE * i;
			clip->y = TILE_SIZE * j;
			clip->w = clip->h = TILE_SIZE;

			// Add this to the sprites
			sprites[i][j] = clip;
		}
	}
	
	//Define the positions of used components from the sprite_sheet
	rect_wall = sprites[0][0];
	rect_floorBrown = sprites[1][0];
	rect_floor = sprites[2][0];
	rect_wallTop = sprites[3][0];
	rect_wallDoor = sprites[0][1];
	rect_wallBottom = sprites[1][1];
	rect_clock1 = sprites[0][2];
	rect_clock2 = sprites[1][2];
	rect_paper1 = sprites[2][2];
	rect_paper2 = sprites[3][2];
	
	//Build the walls
	// Left and Right Walls
	for (int _y = TILE_SIZE; _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y, sprite_sheet, rect_wallTop);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y, sprite_sheet, rect_wallTop);

		// Make them into collidables
        g_game->addCollidable(leftWall, true);
        g_game->addCollidable(rightWall, true);
	}

	// Top and Bottom Walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Don't put walls in the doorways
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*15))
		{
			// Initialise Top and Bottom
			Wall* topWallTop = new Wall(_x, 0, sprite_sheet, rect_wallTop);
			Wall* topWall0 = new Wall(_x, (1*TILE_SIZE), sprite_sheet, rect_wall);
			Wall* topWall1 = new Wall(_x, (2*TILE_SIZE), sprite_sheet, rect_wall);

			// Make them into collidables
			g_game->addCollidable(topWallTop, true);
			g_game->addCollidable(topWall0, true);
			g_game->addCollidable(topWall1, true);
		}
		
		// Add the bottom wall no matter what
		Wall* bottomWall = new Wall(_x, (screen->h - TILE_SIZE), sprite_sheet, rect_wall);
		g_game->addCollidable(bottomWall, true);
	}

	// Left and Right Walls
	for (int _y = (TILE_SIZE*4); _y < (screen->h - TILE_SIZE); _y += TILE_SIZE) // Loop through height
	{
		// Initialise Left and Right
        Wall* leftWall = new Wall(0, _y, sprite_sheet, rect_wallTop);
        Wall* rightWall = new Wall(screen->w - TILE_SIZE, _y, sprite_sheet, rect_wallTop);

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
	delete rect_wallDoor;
    delete rect_wallTop;
	delete rect_floorBrown;
	delete rect_clock1;
	delete rect_clock2;
	delete rect_paper1;
	delete rect_paper2;
}

void Environment::render()
{
	//Build the floor
	for (int i = 0; i < screen->w; i += TILE_SIZE)
		for (int j = 0; j < screen->h; j += TILE_SIZE)
			apply_surface(i, j, sprite_sheet, screen, rect_floor);

	// LEFT Brown floor coin
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 6, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 7, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 8, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 9, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 2, TILE_SIZE * 10, sprite_sheet, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 2, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 5, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 6, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 7, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 6, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 7, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 8, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 9, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 7, TILE_SIZE * 10, sprite_sheet, screen, rect_floorBrown);

	// RIGHT Brown floor coin
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 5, sprite_sheet, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 6, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 7, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 8, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 9, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 10, sprite_sheet, screen, rect_floorBrown);
	
	//apply_surface(TILE_SIZE * 12, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 13, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 15, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 16, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	//apply_surface(TILE_SIZE * 17, TILE_SIZE * 11, sprite_sheet, screen, rect_floorBrown);
	
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 6, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 7, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 8, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 9, sprite_sheet, screen, rect_floorBrown);
	apply_surface(TILE_SIZE * 17, TILE_SIZE * 10, sprite_sheet, screen, rect_floorBrown);


	// Walls that aren't walls
	for (int _x = 0; _x < screen->w; _x += TILE_SIZE) // Loop through width
	{
		// Clock positions
		//if ((_x == TILE_SIZE*3) || (_x == TILE_SIZE*14))
		//	apply_surface(_x - 0.5*TILE_SIZE, 6.5*TILE_SIZE, sprite_sheet, screen, rect_clock1); // Clocks left of doorway
		//if ((_x == TILE_SIZE*5) || (_x == TILE_SIZE*16))
		//	apply_surface(_x + 0.5*TILE_SIZE, 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock2); // Clocks right of doorway

		// Sometimes the bottom of a wall, sometimes a door
		if ((_x != TILE_SIZE*4) && (_x != TILE_SIZE*15))
			apply_surface(_x, 3*TILE_SIZE, sprite_sheet, screen, rect_wallBottom); // Bottom Wall
		else
		{
			apply_surface(_x, 0*TILE_SIZE, sprite_sheet, screen, rect_wallTop); // Top WallTop
			apply_surface(_x, 1*TILE_SIZE, sprite_sheet, screen, rect_wall); // Top Wall
			apply_surface(_x, 2*TILE_SIZE, sprite_sheet, screen, rect_wall); // Mid Wall
			apply_surface(_x, 3*TILE_SIZE, sprite_sheet, screen, rect_wallDoor); // Door
		}

		// Bottom overhang
		apply_surface(_x, (screen->h - 2*TILE_SIZE), sprite_sheet, screen, rect_wallTop);
		
	}

	// Clocks
	apply_surface(TILE_SIZE*4, 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock1); // Clock above left doorway
	apply_surface(TILE_SIZE*15, 1.5*TILE_SIZE, sprite_sheet, screen, rect_clock2); // Clock above left doorway
	
	// Papers
	apply_surface(TILE_SIZE * 3, TILE_SIZE * 12, sprite_sheet, screen, rect_paper1);
	apply_surface(TILE_SIZE * 4, TILE_SIZE * 6, sprite_sheet, screen, rect_paper2);
	apply_surface(TILE_SIZE * 14, TILE_SIZE * 10, sprite_sheet, screen, rect_paper1);
	apply_surface(TILE_SIZE * 9, TILE_SIZE * 9, sprite_sheet, screen, rect_paper2);
	apply_surface(TILE_SIZE * 12, TILE_SIZE * 5, sprite_sheet, screen, rect_paper1);
	apply_surface(TILE_SIZE * 18, TILE_SIZE * 7, sprite_sheet, screen, rect_paper2);

	//Build the whatever man
	//Top Left triangle
	//apply_surface(TILE_SIZE, TILE_SIZE, sprite_sheet, screen, shiny_block);
	//apply_surface((TILE_SIZE*2), TILE_SIZE, sprite_sheet, screen, shiny_block);
	//apply_surface(TILE_SIZE, (TILE_SIZE*2), sprite_sheet, screen, shiny_block);
	//
	////Top Right triangle
	//apply_surface(screen->w - (2*TILE_SIZE), TILE_SIZE, sprite_sheet, screen, shiny_block);
	//apply_surface(screen->w - (2*TILE_SIZE), (TILE_SIZE*2), sprite_sheet, screen, shiny_block);
	//apply_surface(screen->w - (3*TILE_SIZE), TILE_SIZE, sprite_sheet, screen, shiny_block);
	//
	////Bottom Left triangle
	//apply_surface(TILE_SIZE, screen->h - (2*TILE_SIZE), sprite_sheet, screen, shiny_block);
	//apply_surface((TILE_SIZE*2), screen->h - (2*TILE_SIZE), sprite_sheet, screen, shiny_block);
	//apply_surface(TILE_SIZE, screen->h - (3*TILE_SIZE), sprite_sheet, screen, shiny_block);
	//
	////Bottom Right triangle
	//apply_surface(screen->w - (2*TILE_SIZE), screen->h - (2*TILE_SIZE), sprite_sheet, screen, shiny_block);
	//apply_surface(screen->w - (3*TILE_SIZE), screen->h - (2*TILE_SIZE), sprite_sheet, screen, shiny_block);
	//apply_surface(screen->w - (2*TILE_SIZE), screen->h - (3*TILE_SIZE), sprite_sheet, screen, shiny_block);

}


