#include "Player.h"

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) : Entity(x, y), direction(DOWN), moving(false)
{
	delay = 200;
	max_cycles = 3;

	//Initialise the clips of the sprite_sheet
	int clip_w = (sprite_sheet->w / 3);
	int clip_h = (sprite_sheet->h / 4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_Rect* clip = sprites[i][j];

			clip->x = clip_w * j;
			clip->y = clip_h * i,
			
			clip->w = clip_w;
			clip->h = clip_h;
		}
	}
}

void Player::update()
{
	inc_cycle();
	cycle = moving ? cycle : STILL;
}