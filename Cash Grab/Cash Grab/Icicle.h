#pragma once
#include "PhysicsObject.h"
#include "GameObject.h"
#include <list>
#include "Resources.h"
#include "Hazard.h"
#include "ThrowableQuantity.h"
using namespace std;

#define BLAST_SUPPRESSION 0

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
};

#undef BLASH_SUPPRESSION
#undef DAMAGE_PERCENTAGE
