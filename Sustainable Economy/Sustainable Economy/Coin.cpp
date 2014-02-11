#include "Coin.h"

Coin::Coin(void)
{
	x = ex;
	y = ey;
	
	delay = 200;
	max_cycles = 8;

	//Initialise the clips of the sprite_sheet	
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = sprites[i];

		clip->x = clip->y = square_size * i,
		clip->w = clip->h = square_size;
	}
}

void Coin::update()
{
    inc_cycle();
}

Coin::~Coin(void)
{
}