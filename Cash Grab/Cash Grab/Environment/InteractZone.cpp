#include "InteractZone.h"

list<InteractZone*> g_interactZones = list<InteractZone*>();

InteractZone::InteractZone(SDL_Rect* area, function<void ()> func, const int requiredDirection) 
	: OnInteract(func), m_Area(area), m_RequiredDirection(requiredDirection), m_Active(true)
{ 
	g_interactZones.push_back(this); 
}

InteractZone::~InteractZone(void) 
{ 
	g_interactZones.remove(this); 
}

const bool InteractZone::OverlapsWith(const SDL_Rect* rect, const int dir)
{
	// Always return false is inactive
	if (!m_Active)
		return false;

	if (m_RequiredDirection != Player::Direction::NULLDIR)
		if (dir != m_RequiredDirection)
			return false;
	// Only return true if overlapping on all sides
	if (!(rect->x < m_Area->x+m_Area->w)) // Over Right
		return false;
	else if (!(rect->x + rect->w > m_Area->x)) // Over Left
		return false;
	else if (!(rect->y < m_Area->y+m_Area->h)) // Over Top
		return false;
	else if (!(rect->y + rect->h > m_Area->y)) // Over Bottom
		return false;
	else 
		return true;
}
