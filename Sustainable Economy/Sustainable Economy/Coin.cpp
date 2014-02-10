#include "Coin.h"


Coin::Coin(void)
{
	delay = 200;
	max_cycles = 3;

	//Initialise the clips of the sprite_sheet
	//clip = 32
	
	for (int j = 0; j < 3; j++)
	{
		SDL_Rect* clip = sprites[i][j];

		clip->x = clip_w * j;
		clip->y = clip_h * i,
			
		clip->w = clip_w;
		clip->h = clip_h;
	}
}

void Coin::update()
{
    
}

void Coin::render()
{
    
}

Coin::~Coin(void)
{
}
