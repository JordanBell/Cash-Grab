#include "Player.h"
#include "Game.h"
#include "Resources.h"

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) : Collidable(x, y), direction(DOWN), moving(false), m_CanMove(true)
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
    // If it's possible to move or moving in a different direction
    if (m_CanMove || direction != this->direction)
    {
        m_CanMove = true;
        moving = true;
        this->direction = direction;
    }
}

void Player::stop_moving()
{
    moving = false;
}

void Player::SetCanMove(bool canMove)
{
    m_CanMove = canMove;
    
    if (!canMove)
    {
        moving = false;
        SnapToGrid();
    }
}

void Player::SnapToGrid()
{
    // Get grid position based on middle of the player
    int gridX = (x + m_HitBox->w / 2) / TILE_SIZE;
    int gridY = (y + m_HitBox->h / 2) / TILE_SIZE;
    
    // Snap to coordinates
    if (direction == LEFT || direction == RIGHT)
    {
        x = gridX * TILE_SIZE;
    }
    else
    {
        y = gridY * TILE_SIZE;
    }
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
		int pixelsToMove = SPEED * delta;//1000 / 60;
		
		y -= (this->direction == UP)	* pixelsToMove;
		y += (this->direction == DOWN)	* pixelsToMove;
		x -= (this->direction == LEFT)	* pixelsToMove;
		x += (this->direction == RIGHT) * pixelsToMove;
	}
    
    Collidable::update(delta);
}