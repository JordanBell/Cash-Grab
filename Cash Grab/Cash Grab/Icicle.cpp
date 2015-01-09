#include "Icicle.h"
#include "Dispenser.h" // Import this to get the #define for dispensing by type
#include "Resources.h"

#define RENDER_OFFSET XY(-16, -64)
#define BLAST_RADIUS (2*TILE_SIZE)
#define ICICLE_HEIGHT 1000
#define DAMAGE_DURATION 10
#define DAMAGE_WIDTH (0.7f*TILE_SIZE)
#define DAMAGE_HEIGHT (0.8f*TILE_SIZE)
#define SHADOW_SPRITES_NUM 3

list<Icicle*> g_icicles = list<Icicle*>();

Icicle::Icicle(DispenseList* dispenseList, const Position& dropPos)
		: GameObject(dropPos.x, dropPos.y - ICICLE_HEIGHT), 
		PhysicsObject(dropPos.x, dropPos.y, ICICLE_HEIGHT), 
		m_DispenseList(dispenseList), 
		m_DropPos(dropPos), 
		m_CounterToDeletion(DAMAGE_DURATION) 
{
	g_icicles.push_back(this);

	m_imageSurface = g_resources->GetIcicle();
	m_ShadowSurface = g_resources->GetIcicleShadow();

	// Initialise the hitbox
	m_HitBox = new SDL_Rect();
	m_HitBox->w = DAMAGE_WIDTH;
	m_HitBox->h = DAMAGE_HEIGHT;
	m_HitBox->x = dropPos.x - DAMAGE_WIDTH/2;
	m_HitBox->y = dropPos.y - DAMAGE_HEIGHT/2;

	// Lower gravity, since dropping from a high height (so that it's off screen) means it'll go too fast with normal gravity.
    SetGravity(m_gravityForce/10);

	m_renderPriority = LAYER_UI;
	
	// TODO: Add a shadow below
}

Icicle::~Icicle(void) 
{ 
	g_icicles.remove(this); 
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


const Position Icicle::GetLaunchTo(void)
{
	// TODO make sure it doesn't go into walls
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
	// For everything in the dispense list, throw them around
	for (auto dispensePair : *m_DispenseList)
	{
		string type = dispensePair.first;
		int& amount = dispensePair.second;

		for (amount; amount > 0; amount--)
		{
			Position launchPos = Position(x, y);
			int launchAmount = 1;
			DISPENSE_BY_TYPE
		}
	}

	// The dispense list has been expended.
	delete m_DispenseList;
}

const bool Icicle::OverlapsWith(SDL_Rect* rect)
{
	// Only return true if overlapping on all sides
	if (!(rect->x < m_HitBox->x+m_HitBox->w)) // Over Right
		return false;
	else if (!(rect->x + rect->w > m_HitBox->x)) // Over Left
		return false;
	else if (!(rect->y < m_HitBox->y+m_HitBox->h)) // Over Top
		return false;
	else if (!(rect->y + rect->h > m_HitBox->y)) // Over Bottom
		return false;
	else 
		return true;
}
