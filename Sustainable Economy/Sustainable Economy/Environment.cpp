#include "Environment.h"

Environment::Environment(void)
{
	//Set the bounds for the clips from the sprite_sheet
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SDL_Rect* clip = sprites[i][j];

			clip->x = square_size * i;
			clip->y = square_size * j,
			
			clip->w = clip->h = square_size;
		}
	}
	
	//Define the positions of used components from the sprite_sheet
	SDL_Rect* floor = sprites[7][1];
	SDL_Rect* wall = sprites[6][0];
	SDL_Rect* shiny_block = sprites[2][4];

	//Build the floor
	for (int i = 0; i < (screen->w / square_size); i += square_size)
	{
		for (int j = 0; j < (screen->h / square_size); i += square_size)
		{
			apply_surface(i, j, sprite_sheet, entire_image, floor);
		}
	}
	
	//Build the walls
	for (int i = 0; i < (screen->w / square_size); i += square_size) //For all of the width
	{
		if (i == 0 || i == (screen->w / square_size)) //If at the edged widths
		{
			for (int j = 0; j < (screen->h / square_size); i += square_size) //For all of the height
			{
				apply_surface(i, j, sprite_sheet, entire_image, floor);
			}
		}
		else //If not at the edge
		{
			//Just the sides
			apply_surface(i, 0, sprite_sheet, entire_image, floor);
			apply_surface(i, screen->h - square_size, sprite_sheet, entire_image, floor);
		}
	}

	//Build the whatever man
	//Top Left triangle
	apply_surface(square_size, square_size, sprite_sheet, entire_image, shiny_block);
	
	//Top Right triangle
	apply_surface(screen->w - (2*square_size), 1, sprite_sheet, entire_image, shiny_block);
	
	//Bottom Left triangle
	apply_surface(square_size, screen->h , sprite_sheet, entire_image, shiny_block);
	
	//Bottom Right triangle
	apply_surface(screen->w - (2*square_size), screen->h - (2*square_size), sprite_sheet, entire_image, shiny_block);
}

void Environment::render()
{
	apply_surface(x, y, entire_image, screen);
}


