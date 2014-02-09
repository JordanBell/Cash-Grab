#include "Player.h"

//Initialise the size and position of each sprite clip
Player::Player(void)
{
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

void Player::set_skin()
{
	skin = sprites[direction][cycle];
}

void Player::update()
{
	
}

void Player::render()
{
	set_skin();
	apply_surface(x, y, sprite_sheet, screen, skin);
}