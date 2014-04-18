#include "Player.h"
#include "Resources.h"

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) : Collidable(x, y), direction(DOWN), moving(false)
{
	sprite_sheet = g_resources->GetPlayerSheet();

	delay = 200;
	max_cycles = 3 * WALK_SPEED;

	//Initialise the clips of the sprite_sheet
	int clip_w = (sprite_sheet->w / 3);
	int clip_h = (sprite_sheet->h / 4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = clip_w * j;
			clip->y = clip_h * i,
			
			clip->w = clip_w;
			clip->h = clip_h;

			sprites[i][j] = clip;
		}
	}
}

void Player::move(int direction)
{
	moving = true; 
	this->direction = direction;
}
	
void Player::IncCycle(void) 
{
	cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; 
}

void Player::update(int delta)
{
	IncCycle();

	if (moving)
	{
		int pixelsToMove = SPEED*delta;
		
		y -= (this->direction == UP)	* pixelsToMove;
		y += (this->direction == DOWN)	* pixelsToMove;
		x -= (this->direction == LEFT)	* pixelsToMove;
		x += (this->direction == RIGHT) * pixelsToMove;
	}
    
    Collidable::update(delta);
}