#include "Player.h"
#include "Game.h"
#include "Resources.h"

Player *g_player = nullptr;

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) 
	: Collidable(x, y), direction(DOWN), moving(false), m_CanMove(true), smashCount(SMASH_LIMIT), m_evasion1(false), m_evasion2(false)
{
    sprite_sheet = g_resources->GetPlayerSheet();
    
    delay = 200;
    max_cycles = WALK_CYCLE_LENGTH * WALK_SPEED;
    
    //Initialise the clips of the sprite_sheet
    int clip_w = (sprite_sheet->w / WALK_CYCLE_LENGTH);
    int clip_h = (sprite_sheet->h / 4);
    m_HitBox->w = m_AABB->w = clip_w;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < WALK_CYCLE_LENGTH; j++)
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

Player::~Player(void)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            delete sprites[i][j];
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

void Player::Smash(int radius)
{
	// Get all coins in the radius
	list<Coin*> radiusCoins = Coin::CoinsAroundPlayer(radius);

	float forcePercentage;

	const int MAX_RADIUS = 300;
	const int MIN_RADIUS = 100;
	const float MIN_PERCENTAGE = 0.35f;

	if (radius <= MIN_RADIUS)	   forcePercentage = 1.0f;
	else if (radius >= MAX_RADIUS) forcePercentage = MIN_PERCENTAGE;
	else
	{
		float f1 = float(radius - MIN_RADIUS) / float(MAX_RADIUS - MIN_RADIUS);
		float f2 = (f1 * 0.50f);
		forcePercentage = 1.00f - f2;
	}

	for (Coin* c : radiusCoins)
	{
		int dx = x - c->x;
		int dy = y - c->y;
		dx *= forcePercentage;
		dy *= forcePercentage;
		c->LaunchTo(c->x+dx, c->y+dy);
	}
}

void Player::DoMove()
{
    if (moving)
    {
        y += m_yVel;
        x += m_xVel;
        m_AABB->x = x;
        m_AABB->y = y;
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
//        SnapToGrid();
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
	SmashUpdate();
	
	// Could this next block be moved to their corresponding Effect classes?
//	if (m_evasion1)
//	{
//		// Evasion Effect 1 -- Bounce around the player
//		list<Coin*> closeCoins = Coin::CoinsAroundPlayer(MAGNETISM_DISTANCE);
//
//		for (Coin* c : closeCoins)
//			c->LaunchTo(x + (rand()%50 - 25), y + (rand()%50 - 25), 0);
//	}
//	else if (m_evasion2)
//	{
//		// Evasion Effect 2 -- Bounce around the map
//		list<Coin*> closeCoins = Coin::CoinsAroundPlayer(MAGNETISM_DISTANCE);
//
//		for (Coin* c : closeCoins) 
//		{
//			int coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
//			int coinY = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE;
//			c->LaunchTo(coinX, coinY, 2);
//		}
//	}
    
    m_xVel = m_yVel = 0;
    m_AABB->x = x;
    m_AABB->y = y;
    m_AABB->w = sprites[0][0]->w;
    m_AABB->h = sprites[0][0]->h;
    
    if (moving) {
        int pixelsToMove = SPEED * delta;//1000 / 60;
        
        switch (this->direction) {
            case UP:
                m_yVel = -pixelsToMove;
                m_AABB->y = y + m_yVel;
                break;
            case DOWN:
                m_yVel = pixelsToMove;
                break;
            case LEFT:
                m_xVel = -pixelsToMove;
                m_AABB->x = x + m_xVel;
                break;
            case RIGHT:
                m_xVel = pixelsToMove;
                break;
            default:
                break;
        }
        
        m_AABB->h += m_yVel;
        m_AABB->w += m_xVel;
    }
    
    Collidable::update(delta);
}

void Player::SmashUpdate(void)
{
	// Not fully complete
	if (smashCount < SMASH_LIMIT)
	{
		smashCount++;
		if (smashCount % SMASH_INTERVAL == 0)
			Smash(smashCount/2);
	}
}


void Player::render()
{
    // For debugging!
    
    // Draw the AABB, then the player
    /*SDL_Surface *test = g_resources->GetTestImage();
    
    SDL_Rect r = { 0, 0, m_AABB->w, m_AABB->h };
    SDL_Rect *rect = &r;
    apply_surface(m_AABB->x, m_AABB->y, test, screen, rect);*/
    
    Entity::render();
}



















