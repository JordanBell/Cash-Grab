#include "Player.h"
#include "Game.h"
#include "Resources.h"
#include "ParticleSimple.h"
#include "Camera.h"

Player *g_player = nullptr;

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) 
	: Collidable(x, y), Sprite(x, y), direction(DOWN), moving(false), m_CanMove(true), m_TargetVelocities(0, 0),
	smashCount(SMASH_LIMIT), m_evasion1(false), m_evasion2(false), m_speed(MIN_SPEED)
{
    m_imageSurface = g_resources->GetPlayerSheet();
		
    m_animationDelay = 200;
    m_maxCycles = WALK_CYCLE_LENGTH * WALK_SPEED;

	InitSprites();

	m_renderPriority = LAYER_PLAYER;
}

void Player::InitSprites(void)
{
	//Initialise the clips of the m_imageSurface
    int clip_w = (m_imageSurface->w / WALK_CYCLE_LENGTH);
    int clip_h = (m_imageSurface->h / 4);
    m_HitBox->w = m_AABB->w = clip_w;
	m_HitBox->h = m_AABB->h = clip_h/2;

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
    if (m_CanMove)
    {
		y += m_Velocities.y;
		x += m_Velocities.x;

		UpdateCollidablePos(x, y+m_HitBox->h);
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

void Player::Update(int delta)
{
	// Update Friction
	m_Friction = Room::GetPlayerRoom()->GetFriction();

    //IncCycle();
	Sprite::Update(delta);
	SmashUpdate();

	if (m_speed > MIN_SPEED) // Only calculate new speeds if above minimum
		DecaySpeed();

	InitSprites();
    
    m_AABB->w = sprites[0][0]->w;
    m_AABB->h = sprites[0][0]->h/2;
    m_AABB->x = x;
    m_AABB->y = y+m_AABB->h;

	// If the player is moving fast, kick up dirt
	if (!((m_Velocities.x == 0) && (m_Velocities.y == 0))) // If not still
		if (ComputeSpeedPercentage() > 0.75f) // If going fast enough to kick up dirt
			AddDirtParticles();

    if (moving) {
		float pixelsToMove = m_speed * 1000 / 60; //delta

		// Calculate target Y velocity
		if (this->direction == UP) {
			m_TargetVelocities.y = -pixelsToMove;
			m_AABB->y = y + m_AABB->h + m_Velocities.y;
		}
		else if (this->direction == DOWN)
			m_TargetVelocities.y = pixelsToMove;
		else // No input (vertical)
			m_TargetVelocities.y = 0; 

		// Calculate target X velocity
		if (this->direction == LEFT) {
			m_TargetVelocities.x = -pixelsToMove;
			m_AABB->x = x + m_Velocities.x;
		}
		else if (this->direction == RIGHT)
			m_TargetVelocities.x = pixelsToMove;
		else // No input (horizontal)
			m_TargetVelocities.x = 0;

		// The player has moved, so make sure he's still in the same room
		g_camera->FocusOnPlayerRoom();
    } 
	else 
	{
		m_TargetVelocities.x = 0;
		m_TargetVelocities.y = 0;
	}
	
	// Adjust the actual velocity to accelerate toward the set target velocities
	ApproachTargetVelocity();

	// Update AABB based on the new velocities
	if (this->direction == UP)
		m_AABB->y = y + m_AABB->h + m_Velocities.y;

	if (this->direction == LEFT)
		m_AABB->x = x + m_Velocities.x;
    
	m_AABB->w += fabs(m_Velocities.x);
    m_AABB->h += fabs(m_Velocities.y);

    UpdateCollidablePos(x, y);
}

void Player::ApproachTargetVelocity(void)
{
	int polY = m_Velocities.y > 0 ? 1 : -1;

	// (x) Horizontal
	if (m_Velocities.x != m_TargetVelocities.x)
	{
		const int pol = (m_TargetVelocities.x - m_Velocities.x) > 0 ? 1 : -1;

		const double acceleration = moving? 3*m_Friction : m_Friction;
		const float changeInVelocity = pol * min((float)acceleration, fabsf(m_TargetVelocities.x - m_Velocities.x));

		m_Velocities.x += changeInVelocity;
	}

	// (y) Vertical
	if (m_Velocities.y != m_TargetVelocities.y)
	{
		const int pol = (m_TargetVelocities.y - m_Velocities.y) > 0 ? 1 : -1;
		
		const double acceleration = moving? 3*m_Friction : m_Friction;
		const float changeInVelocity = pol * min((float)acceleration, fabsf(m_TargetVelocities.y - m_Velocities.y));

		m_Velocities.y += changeInVelocity;
	}

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
	float minSpeed = MAX_SPEED * 0.75;
	float aboveMin = m_speed - minSpeed;
	float perc = float(aboveMin) / float(MAX_SPEED-minSpeed);
	int angle = 6*perc + 80; // Angle between 80 and 85
	
	// 1 to 4 particles
	int numParticles = perc*perc*3 + 1;
	
	for (int i = 0; i < numParticles; i++)
	{
		// Number of particles created depends on the speed
		if (rand()%100 < perc*50) // More likely at higher speeds
		{
			// Dirt starts at bottom of player
			float s_x, s_y; // Start coords
			s_x = this->x + (m_imageRect->w / 2); // Halfway across
			s_y = this->y + m_imageRect->h;	 // Bottom of player

			// Dirt flies somewhere behind the player
			float e_x, e_y; // End coords
			float r1, r2, val1, val2;
			r1 = rand()%8;
			r2 = rand()%8;
			val1 = r1*r1/4;
			val2 = r2*r2/4;
			val1 *= rand()%2 ? 1 : -1;
			val2 *= rand()%2 ? 1 : -1;
			e_x = s_x - val1;
			e_y = s_y - val2;

			switch (direction)
			{
				case UP:
					e_y += TILE_SIZE/4;
					break;
				case DOWN:
					e_y -= TILE_SIZE/4;
					break;
				case LEFT:
					e_x += TILE_SIZE/4;
					break;
				case RIGHT:
					e_x -= TILE_SIZE/4;
					break;
			}

			ParticleSimple* dirtParticle = new ParticleSimple(s_x, s_y, e_x, e_y);
			g_game->addGameObject(dirtParticle);

			// Find a variable angle 
			int thisAngle = angle + (rand()%5) - 2; // Vary each particle's angle by an amount varying from -2 to +2

			//int angle = 8*(float(m_speed - (MAX_SPEED * 0.75)) / float(MAX_SPEED-(MAX_SPEED * 0.75))) + 81 + ((rand()%5) - 2);

			dirtParticle->Launch(thisAngle);
		}
	}
}

void Player::Render(void)
{
    // Draw the AABB, then the player. For debugging!
    /*Uint32 aabbColor = SDL_MapRGB(g_resources->GetEnvironmentImage()->format, 0x0, 0xFF, 0);
    Uint32 hitBoxColor = SDL_MapRGB(g_resources->GetEnvironmentImage()->format, 0x0, 0, 0xFF);

    SDL_Rect r1 = { m_AABB->x+s_renderingOffset_x, m_AABB->y+s_renderingOffset_y, m_AABB->w, m_AABB->h };
    SDL_Rect r2 = { m_HitBox->x+s_renderingOffset_x, m_HitBox->y+s_renderingOffset_y, m_HitBox->w, m_HitBox->h };
    SDL_FillRect(screen, &r1, aabbColor);
    SDL_FillRect(screen, &r2, hitBoxColor);*/
    
    Sprite::Render();
}
