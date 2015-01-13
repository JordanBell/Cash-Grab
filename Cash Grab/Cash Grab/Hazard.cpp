#include "Hazard.h"

list<Hazard*> Hazard::s_Hazards = list<Hazard*>();

Hazard::Hazard(const int x, const int y, const int w, const int h)
	: m_Active(true), m_DamagePercentage(DEFAULT_DAMAGE) 
{
	// Add this to the static list
	s_Hazards.push_back(this);

	// Construct the area with the arguments
	m_Area = new SDL_Rect();
	m_Area->x = x;
	m_Area->y = y;
	m_Area->w = w;
	m_Area->h = h;
}

Hazard::Hazard(const int x, const int y, const int w, const int h, const float damagePercentage)
	: m_Active(true), m_DamagePercentage(damagePercentage) 
{
	// Add this to the static list
	s_Hazards.push_back(this);

	// Construct the area with the arguments
	m_Area = new SDL_Rect();
	m_Area->x = x;
	m_Area->y = y;
	m_Area->w = w;
	m_Area->h = h;
}

Hazard::~Hazard(void) 
{ 
	s_Hazards.remove(this);
	delete m_Area; 
}


const bool Hazard::OverlapsInEffect(const SDL_Rect* rect) const
{
	// Only check overlap if active
	if (m_Active) 
		return RectIntersect(m_Area, rect); 
	else 
		return false; 
}

const list<Hazard*> Hazard::GetActiveHazards(void)
{
	// Construct a return list
	list<Hazard*> r_activeHazards = list<Hazard*>();

	// Add all hazards that are active
	for (Hazard* hptr : s_Hazards)
		if (hptr->IsActiveHazard())
			r_activeHazards.push_back(hptr);

	// Return the list
	return r_activeHazards;
}

