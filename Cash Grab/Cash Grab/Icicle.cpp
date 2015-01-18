#include "Icicle.h"
#include "Resources.h"
#include "Game.h"

#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"
#include "PowerupMagnetism.h"
#include "PowerupPull.h"
#include "PowerupSmash.h"

#define RENDER_OFFSET XY(-16, -64)
#define BLAST_RADIUS (2*TILE_SIZE)
#define ICICLE_HEIGHT 1000
#define DAMAGE_DURATION 10
#define DAMAGE_WIDTH (0.7f*TILE_SIZE)
#define DAMAGE_HEIGHT (0.8f*TILE_SIZE)
#define SHADOW_SPRITES_NUM 3

#define HAZARD_AREA dropPos.x - DAMAGE_WIDTH/2,\
					dropPos.y - DAMAGE_HEIGHT/2,\
					DAMAGE_WIDTH,\
					DAMAGE_HEIGHT

Icicle::Icicle(DispenseList* dispenseList, const Position& dropPos)
		: GameObject(dropPos.x, dropPos.y - ICICLE_HEIGHT), 
		PhysicsObject(dropPos.x, dropPos.y, ICICLE_HEIGHT), 
		Hazard(HAZARD_AREA),
		m_DispenseList(dispenseList), 
		m_DropPos(dropPos), 
		m_CounterToDeletion(DAMAGE_DURATION) 
{
	m_imageSurface = g_resources->GetIcicle();
	m_ShadowSurface = g_resources->GetIcicleShadow();

	// Lower gravity, since dropping from a high height (so that it's off screen) means it'll go too fast with normal gravity.
    SetGravity(m_gravityForce/10);

	m_renderPriority = LAYER_UI;

	// Set the hazard as initially inactive
	Hazard_Deactivate();
}

void Icicle::Update(int delta) 
{
	PhysicsObject::MoveUpdate();
	GameObject::Update(delta);
		
	// Take on the position calculated as a physics object
	x = GetPOPosition().x;
	y = GetPOPosition().y;

	// If landed, update deletion counter
	if (!IsAirborne())
	{
		m_CounterToDeletion--;

		// Delete self after counter reaches 0
		if (m_CounterToDeletion <= 0)
			g_game->removeGameObject(this);
	}
}

void Icicle::Render(void)
{ 
	if (IsAirborne()) 
	{
		GameObject::Render(RENDER_OFFSET);

		// Render the shadow at the end position
		Position endPos = GetEndPosition();

		// The index for the shadow's size is based on the height of the icicle
		int shadowIndex = ((float)GetHeight() / (float)ICICLE_HEIGHT) * SHADOW_SPRITES_NUM;
		if (shadowIndex < SHADOW_SPRITES_NUM)
		{
			// Get a rect based on that index
			SDL_Rect* shadowSprite = new SDL_Rect();
			shadowSprite->x = shadowIndex * TILE_SIZE;
			shadowSprite->y = 0;
			shadowSprite->w = TILE_SIZE;
			shadowSprite->h = TILE_SIZE/2;

			apply_surface(endPos.x - TILE_SIZE/2, endPos.y - TILE_SIZE/4, m_ShadowSurface, screen, shadowSprite); 

			delete shadowSprite;
		}
	}
}

const Position Icicle::GetLaunchTo(void) const
{
	// Get a random position in a circle
	float randDistance = rand()%(100*BLAST_RADIUS) / 100.0f; // 0 to BLAST_RADIUS, to 2 decimal places
	float randAngle = (rand()%628) / 100.0f; // 0 to 2*PI (imprecise, but that's fine)

	Position circlePosition = Position();
	circlePosition.x = x + randDistance * cos(randAngle) - 16;
	circlePosition.y = y + randDistance * sin(randAngle);

	return circlePosition;
}

void Icicle::OnLanding(void)
{
	// Activate this hazard for damage checking
	Hazard_Activate();

	// For everything in the dispense list, throw them around
	for (auto& throwableQuantity : *m_DispenseList)
		throwableQuantity->ThrowAll(Position(x, y), std::bind(&Icicle::GetLaunchTo, this));
}
