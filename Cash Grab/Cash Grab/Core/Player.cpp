#include "Player.h"
#include "Game.h"
#include "Resources.h"
#include "ParticleSimple.h"
#include "Camera.h"
#include "SpeechBubble.h"
#include "InteractZone.h"
#include "Room.h"
#include "FirePit.h"
#include "Inventory.h"

#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"

#define ON_DAMAGE_IMMUNITY 150
#define DAMAGE_IMMUNITY_FLASH_RATE 5
#define DAMAGE_COIN_LOSS_RADIUS (2*TILE_SIZE)

Player *g_player = nullptr;

//Initialise the size and position of each sprite clip
Player::Player(int x, int y) 
	: Collidable(x, y), Sprite(x, y), direction(DOWN), moving(false), m_CanMove(true), m_TargetVelocities(0, 0),
	smashCount(SMASH_LIMIT), m_evasion1(false), m_evasion2(false), m_speed(MIN_SPEED), 
	m_Speech(nullptr), m_Interaction(nullptr), m_Prompt(nullptr), m_DamageImmunityCounter(0), m_Debug(false)
{
    m_imageSurface = g_resources->GetPlayerSheet();
		
    //m_animationDelay = 200;
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

void Player::Interact(void) 
{ 
	try 
	{
		if (m_Interaction) 
			m_Interaction->OnInteract(); 
	}
	catch (string s)
	{
		Say(s, false);
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

//// Say something indefinitely - without timeout
//void Player::SayIndef(const string phrase)
//{
//	// Delete the old SpeechBubble, if exists.
//	if (m_Speech)
//		m_Speech->Deactivate();
//	
//	// Create the new speech bubble
//	SpeechBubble* newSpeech = new SpeechBubble(this, phrase);
//
//	// Add it to the game loop and set it as the player's speech
//	g_game->addGameObject(newSpeech);
//	m_Speech = newSpeech;
//}


void Player::Say(const string phrase, bool useProportionalTimeout)
{
	// Delete the old SpeechBubble, if exists.
	/*if (m_Speech)
		(*m_Speech)->Deactivate();*/
	
	// Create the new speech bubble
	int timeout = useProportionalTimeout? 20*phrase.length() : 200;
	if (m_Speech)
	{
		m_Speech->SetPhrase(phrase);
		m_Speech->SetTimeout(timeout);
		m_Speech->Activate();
	}
	else
	{
		m_Speech = new SpeechBubble(this, phrase, timeout);
		g_game->addGameObject(m_Speech);
	}
}

void Player::ReplaceSpeech(SpeechBubble* sPtr)
{
	static int speechCount = 0;
	speechCount++;
	printf("Speech #%d\n", speechCount);

	// Delete the current speech
	//if (m_Speech) g_game->removeGameObject(*m_Speech);
	if (m_Speech) (m_Speech)->Deactivate();

	// Set argument as the new speach
	m_Speech = sPtr;

	// Add it to the game loop and set it as the player's speech
	g_game->addGameObject(m_Speech);
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
	// Handle Sprite Update
	Sprite::Update(delta);

	// Update the beta update for the smash ability
	SmashUpdate();

	// Update Friction
	m_Friction = Room::GetPlayerRoom()->GetFriction();

	if (m_Prompt == nullptr)
	{
		m_Prompt = new Prompt(this);
		g_game->addGameObject(m_Prompt);
	}

	if (m_speed > MIN_SPEED) // Only calculate new speeds if above minimum
		DecaySpeed();
    
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

	// Check again for if this is in a zone
	m_Interaction = nullptr;
	for (InteractZone* zone : g_interactZones)
		if (zone->OverlapsWith(m_HitBox, direction))
			m_Interaction = zone;

	m_Prompt->SetVisible(m_Interaction != nullptr);

	// Check for collisions with damage objects
	UpdateDamageDetection();
	
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

void Player::UpdateDamageDetection(void)
{
	// First, check for immunity
	if (m_DamageImmunityCounter <= 0)
	{
		// Check against all fire pits
		for (FirePit* pit : g_firePits)
		{
			if (pit->IsErupting())
				if (pit->OverlapsWith(m_AABB))
					OnDamage(pit->GetDamagePercentage());
		}

		// TODO Check against all existing Stalactites
	}
	else
		m_DamageImmunityCounter--;

}

void Player::SetImmunityCounter(const int newCount)
{
	m_DamageImmunityCounter = newCount;
}

void Player::SetSpeed(const float newSpeed)
{
	m_TargetVelocities.x = m_TargetVelocities.y = m_Velocities.x = m_Velocities.y = m_speed = newSpeed;
}


void Player::OnDamage(const float damagePercentage)
{
	SetImmunityCounter(ON_DAMAGE_IMMUNITY);

	// Slow down the player to minimum speed
	SetSpeed(MIN_SPEED);

	// Find the element of the room to determine the element of the coins lost
	const Element currentRoomElement = g_camera->GetRoomFocus()->GetElement(); 
	// Get the room's wallet
	Wallet* roomWallet = Inventory::GetCoinWallet(currentRoomElement);
	// How much is in that wallet?
	const int numCoinsOwned = roomWallet->GetAmount();
	// Based on the damage percentage, find out how many are dropped
	const int numCoinsLost = (float)numCoinsOwned * damagePercentage;

	// Remove those coins from the wallet
	roomWallet->Remove(numCoinsLost);

	// Get a DispenseList from the current room's dispenser. This will maintain the kinds of coins that were picked up as the dispenser holds that data.
	DispenseList dispenseList = g_camera->GetRoomFocus()->GetDispenser()->DetermineCoinList(numCoinsLost);

	// Throw those coins around the player
	for (auto dispensePair : dispenseList)
	{
		// Throw the coins there
		const string type = dispensePair.first;
		int& amount = dispensePair.second;

		// Launch that amount of coins
		while (amount > 0)
		{
			// Find a random angle around the circle to shoot this to
			Position circlePos = Position();
			Position center = GetCenter();

			float angle = rand()%628; // A value out of 2*pi
			angle /= 100; // Radians

			circlePos.x = x + DAMAGE_COIN_LOSS_RADIUS * cos(angle);
			circlePos.y = y + DAMAGE_COIN_LOSS_RADIUS * sin(angle) * 7/8; // Squish the y-axis a bit

			// Create a new coin object based on the dispense pair's type
			Coin* coin;

			if (type == "bronzecoin")
				coin = new CoinBronze(center.x, center.y, circlePos.x, circlePos.y, currentRoomElement);
			if (type == "silvercoin")
				coin = new CoinSilver(center.x, center.y, circlePos.x, circlePos.y, currentRoomElement);
			if (type == "goldcoin")
				coin = new CoinGold(center.x, center.y, circlePos.x, circlePos.y, currentRoomElement);

			coin->Launch();
			g_game->addCollidable(coin);
			amount--;
		}
	}
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
    if (m_Debug) {
        // Draw the AABB, then the player
        Uint32 aabbColor = SDL_MapRGB(g_resources->GetEnvironmentImage()->format, 0x0, 0xFF, 0);
        Uint32 hitBoxColor = SDL_MapRGB(g_resources->GetEnvironmentImage()->format, 0x0, 0, 0xFF);

        SDL_Rect r1 = { static_cast<Sint16>(m_AABB->x+s_renderingOffset_x), static_cast<Sint16>(m_AABB->y+s_renderingOffset_y), m_AABB->w, m_AABB->h };
        SDL_Rect r2 = { static_cast<Sint16>(m_HitBox->x+s_renderingOffset_x), static_cast<Sint16>(m_HitBox->y+s_renderingOffset_y), m_HitBox->w, m_HitBox->h };
        
        SDL_FillRect(screen, &r1, aabbColor);
        SDL_FillRect(screen, &r2, hitBoxColor);
    }
    
	// Check for recent damage flashing
	if (m_DamageImmunityCounter % (2*DAMAGE_IMMUNITY_FLASH_RATE) < DAMAGE_IMMUNITY_FLASH_RATE) // True half of the time, alternating every 'n' seconds (n = DAMAGE_IMMUNITY_FLASH_RATE)
		Sprite::Render();
}
