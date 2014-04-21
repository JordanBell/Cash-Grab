#include "Environment.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"

Environment* g_environment = NULL;

Environment::Environment(int x, int y) : Entity(x, y)
{
	sprite_sheet = g_resources->GetEnvironmentImage();

	//Set the bounds for the clips from the sprite_sheet
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = square_size * i;
			clip->y = square_size * j;
			clip->w = clip->h = square_size;

			// Add this to the sprites
			sprites[i][j] = clip;
		}
	}
	
	//Define the positions of used components from the sprite_sheet
	floor = sprites[7][1];
	floorBrown = sprites[6][1];
	wall = sprites[6][0];
	shiny_block = sprites[2][4];
	
	//Build the walls
	for (int i = 0; i < screen->w; i += square_size) //For all of the width
	{
		if (i == 0 || i == (screen->w - square_size)) //If at the edged widths
		{
			for (int j = 0; j < screen->h; j += square_size) //For all of the height
			{
                Wall* toAdd = new Wall(i, j, sprite_sheet, wall);
                if (!toAdd) printf("ERROR\n");
                g_game->addCollidable(toAdd, true);
			}
		}
		else //If not at the edge
		{
            Wall* wall1 = new Wall(i, 0, sprite_sheet, wall);
            Wall* wall2 = new Wall(i, screen->h - square_size, sprite_sheet, wall);
            
            if (!wall1 || ! wall2) printf("ERROR\n");
            
			//Just the sides
			g_game->addCollidable(wall1, true);
			g_game->addCollidable(wall2, true);
		}
	}
}

Environment::~Environment()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 5; j++) {
            delete sprites[i][j];
        }
    }
    
    delete floor;
    delete wall;
    delete shiny_block;
}

void Environment::render()
{
	//Build the floor
	for (int i = 0; i < screen->w; i += square_size)
	{
		for (int j = 0; j < screen->h; j += square_size)
		{			
			/*printf("Screen w: %d, h: %d\n", screen->w, screen->h);
			printf("Square size: %d\n", square_size);*/
			apply_surface(i, j, sprite_sheet, screen, floor);
		}
	}

	// LEFT Brown floor coin
	//apply_surface(square_size * 2, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 3, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 4, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 5, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 6, square_size * 5, sprite_sheet, screen, floorBrown);
	//apply_surface(square_size * 7, square_size * 5, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 2, square_size * 6, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 2, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 2, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 2, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 2, square_size * 10, sprite_sheet, screen, floorBrown);
	
	//apply_surface(square_size * 2, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 3, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 4, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 5, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 6, square_size * 11, sprite_sheet, screen, floorBrown);
	//apply_surface(square_size * 7, square_size * 11, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 7, square_size * 6, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 7, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 7, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 7, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 7, square_size * 10, sprite_sheet, screen, floorBrown);
	
	// Filling
	/*apply_surface(square_size * 4, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 5, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 4, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 5, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 4, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 5, square_size * 9, sprite_sheet, screen, floorBrown);*/

	// CONNECTION
	/*apply_surface(square_size * 8, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 9, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 10, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 11, square_size * 7, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 8, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 9, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 10, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 11, square_size * 8, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 8, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 9, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 10, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 11, square_size * 9, sprite_sheet, screen, floorBrown);*/


	// RIGHT Brown floor coin
	//apply_surface(square_size * 12, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 13, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 14, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 15, square_size * 5, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 16, square_size * 5, sprite_sheet, screen, floorBrown);
	//apply_surface(square_size * 17, square_size * 5, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 12, square_size * 6, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 12, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 12, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 12, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 12, square_size * 10, sprite_sheet, screen, floorBrown);
	
	//apply_surface(square_size * 12, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 13, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 14, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 15, square_size * 11, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 16, square_size * 11, sprite_sheet, screen, floorBrown);
	//apply_surface(square_size * 17, square_size * 11, sprite_sheet, screen, floorBrown);
	
	apply_surface(square_size * 17, square_size * 6, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 17, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 17, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 17, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 17, square_size * 10, sprite_sheet, screen, floorBrown);
	
	// Filling
	/*apply_surface(square_size * 14, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 15, square_size * 7, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 14, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 15, square_size * 8, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 14, square_size * 9, sprite_sheet, screen, floorBrown);
	apply_surface(square_size * 15, square_size * 9, sprite_sheet, screen, floorBrown);*/

	//Build the whatever man
	//Top Left triangle
	apply_surface(square_size, square_size, sprite_sheet, screen, shiny_block);
	apply_surface((square_size*2), square_size, sprite_sheet, screen, shiny_block);
	apply_surface(square_size, (square_size*2), sprite_sheet, screen, shiny_block);
	
	//Top Right triangle
	apply_surface(screen->w - (2*square_size), square_size, sprite_sheet, screen, shiny_block);
	apply_surface(screen->w - (2*square_size), (square_size*2), sprite_sheet, screen, shiny_block);
	apply_surface(screen->w - (3*square_size), square_size, sprite_sheet, screen, shiny_block);
	
	//Bottom Left triangle
	apply_surface(square_size, screen->h - (2*square_size), sprite_sheet, screen, shiny_block);
	apply_surface((square_size*2), screen->h - (2*square_size), sprite_sheet, screen, shiny_block);
	apply_surface(square_size, screen->h - (3*square_size), sprite_sheet, screen, shiny_block);
	
	//Bottom Right triangle
	apply_surface(screen->w - (2*square_size), screen->h - (2*square_size), sprite_sheet, screen, shiny_block);
	apply_surface(screen->w - (3*square_size), screen->h - (2*square_size), sprite_sheet, screen, shiny_block);
	apply_surface(screen->w - (2*square_size), screen->h - (3*square_size), sprite_sheet, screen, shiny_block);

}


