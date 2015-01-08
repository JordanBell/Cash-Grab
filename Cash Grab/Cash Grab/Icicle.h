#pragma once
#include "PhysicsObject.h"
#include "GameObject.h"
#include <list>
#include "Resources.h"
using namespace std;

#define BLAST_SUPPRESSION 1
#define DAMAGE_PERCENTAGE 1.0f

typedef list<pair<string, int>> DispenseList;

class Icicle :
	public PhysicsObject, public GameObject
{
public:
	Icicle(DispenseList* dispenseList, const Position& dropPos);

	~Icicle(void);

	void Update(int delta) override final;

	// Only render if in the air. The icicle still exists for a little while after landing, but shouldn't be rendered
	void Render(void) override final { if (IsAirborne()) { y -= 64; x -= 16; GameObject::Render(); x += 16; y += 64;} }

	// Check that a rect overlaps this this one damage area
	const bool OverlapsWith(SDL_Rect* rect);

	float GetDamagePercentage() { return DAMAGE_PERCENTAGE; }

protected:
	// On landing, explode the list of throwables around
	void OnLanding(void) override final;

private:
	DispenseList* m_DispenseList;
	Position m_DropPos;
	int m_CounterToDeletion;
	SDL_Rect* m_HitBox;

	// Get a position in the blast radius for a throwable to go
	const Position GetLaunchTo(void);

	// Launch a particular type of throwable (modified from Dispenser)
	template <class Throw_Type>
	void LaunchThrowable(const Position start, const int count)
	{
		for (int i = 0; i < count; i++)
		{
			// Find this throwable's target position
			Position to = GetLaunchTo();

			// Create a new throwable for that destination
			Throw_Type* throwable = new Throw_Type(start.x, start.y, to.x, to.y, ICE);
			throwable->Launch(BLAST_SUPPRESSION);

			// Add it to the collidables list
			g_game->addCollidable(throwable);
		}
	}
};

extern list<Icicle*> g_icicles;

#undef BLASH_SUPPRESSION
#undef DAMAGE_PERCENTAGE
