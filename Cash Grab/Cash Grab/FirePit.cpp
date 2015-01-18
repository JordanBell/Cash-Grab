#include "FirePit.h"
#include "Resources.h"
#include "ParticleLava.h"

#define HAZARD_AREA x-TILE_SIZE/2,\
					y-TILE_SIZE/4,\
					2*TILE_SIZE,\
					1.5*TILE_SIZE

const float FirePit::k_EruptChance = 0.001f;
const float FirePit::k_TipCurve = 0.3f;
const Dimensions FirePit::k_ParticleSize_Eruption = Dimensions(8, 8);
const Dimensions FirePit::k_ParticleSize_Charge = Dimensions(3, 3);

FirePit::FirePit(const int x, const int y)
	: Sprite(x, y), 
	 Hazard(HAZARD_AREA), 
	m_State(IDLE), m_ChargeCounter(0), m_EruptCounter(0)
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
	const int integerChanceTotal = 1.0f/k_EruptChance;
	const bool eruptTriggered = (rand() % integerChanceTotal) == 0;

	if (eruptTriggered)
		SetState(CHARGING);
}

void FirePit::UpdateCharging(void)
{
	if (m_ChargeCounter < k_TimeCharge)
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
	if (m_EruptCounter < k_TimeErupt)
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
	for (int i = 0; i < k_ParticleNum_Charge; i++)
	{
		// Find the center of the circle
		Position center(x+TILE_SIZE/2 - 2, y+TILE_SIZE*3/4 - 6);

		// Find a random position in the hole's area
		int maxDistance = k_EmitRadius;
		int distance = rand()%100 / 100.0f * maxDistance;
		float angle = rand()%628; 
		angle /= 100.0f;

		// Get the difference in coordinates from the center to construct the "from" position
		int startXChange = distance*cos(angle);
		int startYChange = distance*sin(angle) *5/8; // Squish the y-axis

		Position from(center.x + startXChange, center.y + startYChange);

		float chargePercentage = (float)m_ChargeCounter / k_TimeCharge;
		int endXChange = startXChange * 0.05f*chargePercentage;
		int endYChange = startYChange * 0.05f*chargePercentage;

		Position to(from.x + endXChange, from.y + endYChange);

		ParticleLava* p = new ParticleLava(from.x, from.y, to.x, to.y, k_ParticleSize_Charge);
		p->Launch(1); // Suppress slightly
		if ((from.x == to.x) && (from.y == to.y))
		{
			// Vary bounce height based on distance from center
			float percentage = (float)distance / (float)maxDistance;
			// Make that percentage curve
			percentage *= percentage;
			int bounceHeight = chargePercentage * k_TipHeight/2 * (1.0f - (percentage * k_TipCurve)); // Vary by the percentage given in TIP_CURVE
			p->Bounce(bounceHeight);
		}
		g_game->addGameObject(p);
	}
}

void FirePit::EmitEruption(void)
{
	for (int i = 0; i < k_ParticleNum_Eruption; i++)
	{
		// Find the center of the circle
		Position center(x+TILE_SIZE/2 - 4, y+TILE_SIZE*3/4 - 6);

		// Find a random position in the hole's area
		int maxDistance = k_EruptionRadius;
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

		ParticleLava* p = new ParticleLava(from.x, from.y, to.x, to.y, k_ParticleSize_Eruption);
		p->Launch(89);
		if ((from.x == to.x) && (from.y == to.y))
		{
			// Vary bounce height based on distance from center
			float percentage = (float)distance / (float)maxDistance;
			// Make that percentage curve
			percentage *= percentage * percentage;
			int bounceHeight = k_TipHeight * (1.0f - (percentage * k_TipCurve)); // Vary by the percentage given in TIP_CURVE
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
			const float chargeProgressPercentage = (float)m_ChargeCounter / k_TimeCharge;
			if (chargeProgressPercentage < 1.0f) 
				m_cycle = int(chargeProgressPercentage*(m_maxCycles-1)) + 1;
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
