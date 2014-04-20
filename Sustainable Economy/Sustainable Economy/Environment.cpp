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
                g_game->addCollidable(toAdd);
			}
		}
		else //If not at the edge
		{
            Wall* wall1 = new Wall(i, 0, sprite_sheet, wall);
            Wall* wall2 = new Wall(i, screen->h - square_size, sprite_sheet, wall);
            
            if (!wall1 || ! wall2) printf("ERROR\n");
            
			//Just the sides
			g_game->addCollidable(wall1);
			g_game->addCollidable(wall2);
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
	
//	//Build the walls
//	for (int i = 0; i < screen->w; i += square_size) //For all of the width
//	{
//		if (i == 0 || i == (screen->w - square_size)) //If at the edged widths
//		{
//			for (int j = 0; j < screen->h; j += square_size) //For all of the height
//			{
//				apply_surface(i, j, sprite_sheet, screen, wall);
//			}
//		}
//		else //If not at the edge
//		{
//			//Just the sides
//			apply_surface(i, 0, sprite_sheet, screen, wall);
//			apply_surface(i, screen->h - square_size, sprite_sheet, screen, wall);
//		}
//	}

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


