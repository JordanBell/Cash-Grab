#pragma once
#include "toolkit.h"
#include <list>
using namespace std;

#define DEFAULT_DAMAGE 1.0f

/*
An area that is considered a hazard. 
*/
class Hazard
{
public:
	// Construct a zone with an area using the default damage amount
	Hazard(const int x, const int y, const int w, const int h);
	
	// Construt a zone with an area and a certain amount of damage dealt
	Hazard(const int x, const int y, const int w, const int h, const float damagePercentage);

	virtual ~Hazard(void);

	// Check whether or not the zone's rect overlaps with another rect
	const bool OverlapsInEffect(const SDL_Rect* rect) const;

	// Return the percentage of damage
	const float GetDamagePercentage(void) const
		{ return m_DamagePercentage; }

	// Check whether or not this is active
	const bool IsActiveHazard(void) const
		{ return m_Active; }

	// Return a list of all active hazards
	static const list<Hazard*> GetActiveHazards(void);

protected:
	// Set this hazard zone as active
	void Hazard_Activate(void) { m_Active = true; }
	
	// Set this hazard zone as inactive
	void Hazard_Deactivate(void) { m_Active = false; }

private:
	static list<Hazard*> s_Hazards;
	bool m_Active;
	SDL_Rect* m_Area;
	const float m_DamagePercentage;
};

