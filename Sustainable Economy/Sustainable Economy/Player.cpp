#include "Player.h"
#include "Game.h"
#include "Resources.h"
#include "ParticleSimple.h"

Player *g_player = nullptr;

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) 
	: Collidable(x, y), direction(DOWN), moving(false), m_CanMove(true), smashCount(SMASH_LIMIT), m_evasion1(false), m_evasion2(false), m_speed(MIN_SPEED)
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

		// The boundaries for the screen, player and his trespassings in any four directions
		int screenLeft, playerLeft;
		int screenRight, playerRight;
		int screenTop, playerTop;
		int screenBottom, playerBottom;
		bool offLeft, offRight, offTop, offBottom;

        // Player Boundaries
		playerLeft = x, playerTop = y;
		playerRight = x + skin->w;
		playerBottom = y + skin->h;

        // Screen Boundaries
		screenLeft = -s_renderingOffset_x, screenTop = -s_renderingOffset_y;
		screenRight = screen->w - s_renderingOffset_x;
		screenBottom = screen->h - s_renderingOffset_y;

		// Check for boundary passes
		offLeft   = (direction == LEFT) && (playerLeft < screenLeft);
		offRight  = (direction == RIGHT) && (playerRight > screenRight);
		offTop	  = (direction == UP) && (playerTop < screenTop);
		offBottom = (direction == DOWN) && (playerBottom > screenBottom);

		if (offLeft)   g_game->TransitionScreen(LEFT);
		if (offRight)  g_game->TransitionScreen(RIGHT);
		if (offTop)	   g_game->TransitionScreen(UP);
		if (offBottom) g_game->TransitionScreen(DOWN);
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

void Player::IncSpeed(const float amount) 
{ 
	// Increase the player's speed
	if (amount == 0.03)
		m_speed += amount * (1 - (m_speed - MIN_SPEED) / (MAX_SPEED - MIN_SPEED));
	else
		m_speed += amount; 

	//// Limit to MIN if fallen below
	//m_speed = (m_speed < MIN_SPEED)? 
	//		  MIN_SPEED 
	//		  : m_speed; 

	// Limit to MIN and MAX speeds if exceeding
	m_speed = (m_speed < MIN_SPEED)? 
			  MIN_SPEED 
			  : (m_speed > MAX_SPEED)? 
				  MAX_SPEED 
				  : m_speed; 
}

const float Player::ComputeDecay(void)
{
	// Speed decay varies based on how far it is from minimum
	float diffFromMin = m_speed - MIN_SPEED;
	
	return DECAY_MINIMUM + ((diffFromMin*diffFromMin) * DECAY_FACTOR);
}

void Player::update(int delta)
{
    IncCycle();
	SmashUpdate();

	if (m_speed > MIN_SPEED) // Only calculate new speeds if above minimum
		DecaySpeed();

	//printf("Speed: %f%%\tDecay: -%f%%\n", ComputeSpeedPercentage()*100, ComputeDecay()*100);
	
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
		// If the player is moving fast, kick up dirt
		if (ComputeSpeedPercentage() > 0.75f)
			AddDirtParticles();

        int pixelsToMove = m_speed * 1000 / 60; //delta;

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

void Player::AddDirtParticles(void)
{
	printf("Particles!");

	// Dirt starts at bottom of player
	int s_x, s_y; // Start coords
	s_x = this->x + (skin->w / 2); // Halfway across
	s_y = this->y + skin->h;	 // Bottom of player

	// Dirt flies somewhere behind the player
	int e_x, e_y; // End coords
	int r1, r2;
	r1 = rand()%8;
	r2 = rand()%8;
	e_x = s_x - r1*r1/2;
	e_y = s_y - r2*r2/3;

	ParticleSimple* dirtParticle = new ParticleSimple(s_x, s_y, e_x, e_y);
	dirtParticle->Launch(1);
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



















