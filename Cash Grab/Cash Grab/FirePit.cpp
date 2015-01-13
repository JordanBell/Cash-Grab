#include "FirePit.h"
#include "Resources.h"
#include "Game.h"
#include "ParticleLava.h"

#define ERUPT_CHANCE 0.001f
#define ERUPT_TIME 200.0f
#define CHARGE_TIME 300.0f
#define SIZE_LARGE Dimensions(8, 8)
#define SIZE_SMALL Dimensions(3, 3)
#define NUM_CHARGING 1
#define NUM_ERUPTION 6

// The higher the fraction (up to 1.0) the lower the lava from the edge in the radius of eruption
#define TIP_CURVE 0.3f
// The height of the highest point in the eruption
#define TIP_HEIGHT 13

#define HAZARD_AREA x-8,\
					y-8,\
					TILE_SIZE + 16,\
					TILE_SIZE + 16

FirePit::FirePit(const int x, const int y)
	: Sprite(x, y), 
	 Hazard(HAZARD_AREA), 
	m_State(IDLE), m_EruptChance(ERUPT_CHANCE), m_ChargeCounter(0), m_EruptCounter(0)
{
	// GameObject stuff
	m_renderPriority = LAYER_GROUND;
	m_imageSurface = g_resources->GetFirePit();

	// Sprite stuff
	m_maxCycles = 8;
	InitSprites();

	// Set the hazard as initially inactive
	Hazard_Deactivate();
}

void FirePit::InitSprites(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* rect = new SDL_Rect();
		rect->x = i*TILE_SIZE;
		rect->y = 0;
		rect->w = TILE_SIZE;
		rect->h = TILE_SIZE;

		m_Sprites[i] = rect;
	}
}

void FirePit::SetState(State s) 
{ 
	m_State = s; 

	// Activate or Deactive this hazard, depending on the new state
	if (m_State == ERUPTING)
		Hazard_Activate();
	else
		Hazard_Deactivate();
}

void FirePit::Update(int delta)
{
	// Update based on the state
	switch (m_State)
	{
		case IDLE:		UpdateIdle();	  break;
		case CHARGING:	UpdateCharging(); break;
		case ERUPTING:	UpdateErupting(); break;
		default: throw runtime_error("Unrecognised fire pit state.");
	}

	Sprite::Update(delta);
}

void FirePit::UpdateIdle(void)
{
	// Try chances at eruption
	const int integerChanceTotal = 1.0f/ERUPT_CHANCE;
	const bool eruptTriggered = (rand() % integerChanceTotal) == 0;

	if (eruptTriggered)
		SetState(CHARGING);
}

void FirePit::UpdateCharging(void)
{
	if (m_ChargeCounter < CHARGE_TIME)
	{
		// Still charging
		m_ChargeCounter++;
		
		// Emit bouncy warning particles
		EmitCharge();
	}
	else
	{
		// Charging Finished. Start Eruption.
		m_ChargeCounter = 0;
		SetState(ERUPTING);
	}
}

void FirePit::UpdateErupting(void)
{
	if (m_EruptCounter < ERUPT_TIME)
	{
		// Still erupting
		m_EruptCounter++;

		// Create silly little lava particles
		EmitEruption();
	}
	else
	{
		// Eruption Finished!
		m_EruptCounter = 0;
		SetState(IDLE);
	}
}

void FirePit::EmitCharge(void)
{
	for (int i = 0; i < NUM_CHARGING; i++)
	{
		// Find the center of the circle
		Position center(x+TILE_SIZE/2 - 2, y+TILE_SIZE*3/4 - 6);

		// Find a random position in the hole's area
		int maxDistance = TILE_SIZE*3/4;
		int distance = rand()%100 / 100.0f * maxDistance;
		float angle = rand()%628; 
		angle /= 100.0f;

		// Get the difference in coordinates from the center to construct the "from" position
		int startXChange = distance*cos(angle);
		int startYChange = distance*sin(angle) *5/8; // Squish the y-axis

		Position from(center.x + startXChange, center.y + startYChange);

		float chargePercentage = (float)m_ChargeCounter / CHARGE_TIME;
		int endXChange = startXChange * 0.05f*chargePercentage;
		int endYChange = startYChange * 0.05f*chargePercentage;

		Position to(from.x + endXChange, from.y + endYChange);

		ParticleLava* p = new ParticleLava(from.x, from.y, to.x, to.y, SIZE_SMALL);
		p->Launch(1); // Suppress slightly
		if ((from.x == to.x) && (from.y == to.y))
		{
			// Vary bounce height based on distance from center
			float percentage = (float)distance / (float)maxDistance;
			// Make that percentage curve
			percentage *= percentage;
			int bounceHeight = chargePercentage * TIP_HEIGHT/2 * (1.0f - (percentage * TIP_CURVE)); // Vary by the percentage given in TIP_CURVE
			p->Bounce(bounceHeight);
		}
		g_game->addGameObject(p);
	}
}

void FirePit::EmitEruption(void)
{
	for (int i = 0; i < NUM_ERUPTION; i++)
	{
		// Find the center of the circle
		Position center(x+TILE_SIZE/2 - 4, y+TILE_SIZE*3/4 - 6);

		// Find a random position in the hole's area
		int maxDistance = TILE_SIZE*3/4;
		int distance = rand()%100 / 100.0f * maxDistance + 1; // +1 at the end to prevent distance being 0 - center particles look odd (for some reason)
		float angle = rand()%628; 
		angle /= 100.0f;

		// Get the difference in coordinates from the center to construct the "from" position
		int startXChange = distance*cos(angle);
		int startYChange = distance*sin(angle) *5/8; // Squish the y-axis

		Position from(center.x + startXChange, center.y + startYChange);

		int endXChange = startXChange * 0;
		int endYChange = startYChange * 0;

		Position to(from.x + endXChange, from.y + endYChange);

		ParticleLava* p = new ParticleLava(from.x, from.y, to.x, to.y, SIZE_LARGE);
		p->Launch(89);
		if ((from.x == to.x) && (from.y == to.y))
		{
			// Vary bounce height based on distance from center
			float percentage = (float)distance / (float)maxDistance;
			// Make that percentage curve
			percentage *= percentage * percentage;
			int bounceHeight = TIP_HEIGHT * (1.0f - (percentage * TIP_CURVE)); // Vary by the percentage given in TIP_CURVE
			p->Bounce(bounceHeight);
		}

		g_game->addGameObject(p);
	}
}

void FirePit::IncCycle(void) 
{ 
	switch (m_State)
	{
		case IDLE:		
			m_cycle = 0; // No Charge
			break;

		case CHARGING:	
			{
			float chargePercentage = (float)m_ChargeCounter / CHARGE_TIME;
			if (chargePercentage < 1.0f) 
				m_cycle = int(chargePercentage*(m_maxCycles-1)) + 1;
			}
			break;
		case ERUPTING:	
			m_cycle = m_maxCycles-1; // Max Charge
			break;
		default: 
			throw runtime_error("Unrecognised fire pit state.");
	}
}

const bool FirePit::IsErupting(void) 
{ 
	return (m_State == ERUPTING); 
}
