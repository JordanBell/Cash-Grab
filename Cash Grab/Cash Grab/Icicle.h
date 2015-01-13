#pragma once
#include "PhysicsObject.h"
#include "GameObject.h"
#include <list>
#include "Resources.h"
#include "Hazard.h"
using namespace std;

#define BLAST_SUPPRESSION 0

typedef list<pair<string, int>> DispenseList;

class Icicle :
	public PhysicsObject, public GameObject, public Hazard
{
public:
	Icicle(DispenseList* dispenseList, const Position& dropPos);

	~Icicle(void) {}

	void Update(int delta) override final;

	// Only render if in the air. The icicle still exists for a little while after landing, but shouldn't be rendered
	void Render(void) override final;

protected:
	// On landing, explode the list of throwables around
	void OnLanding(void) override final;

private:
	DispenseList* m_DispenseList;
	Position m_DropPos;
	int m_CounterToDeletion;

	// The icicle's shadow
	SDL_Surface* m_ShadowSurface;

	// Get a position in the blast radius for a throwable to go
	const Position GetLaunchTo(void) const;

	// Dispense a throwable based on a string type
	void DispenseByType(const Position launchPos, const int launchAmount, const string type) const;

	// Launch a particular type of throwable (modified from Dispenser)
	template <class Throw_Type>
	void LaunchThrowable(const Position start, const int count) const
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

#undef BLASH_SUPPRESSION
#undef DAMAGE_PERCENTAGE
