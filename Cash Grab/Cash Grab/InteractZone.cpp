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

	// Return false if the given direction does not match the required direction
	if (m_RequiredDirection != Player::Direction::NULLDIR)
		if (dir != m_RequiredDirection)
			return false;
	
	// If everything is good so far, check the overlap
	return RectIntersect(m_Area, rect);
}
