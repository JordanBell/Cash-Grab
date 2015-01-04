#pragma once
#include "SDL.h"
#include "Player.h"
#include <functional>
#include <list>
using namespace std;

class InteractZone
{
public:
	InteractZone(SDL_Rect* area, function<void ()> func, const int requiredDirection = Player::Direction::NULLDIR);
	~InteractZone(void);

	const bool OverlapsWith(const SDL_Rect* rect, const int dir);
	function<void ()> OnInteract;

	void Deactivate(void) { m_Active = false; }
	void Activate(void) { m_Active = true; }

private:
	SDL_Rect* m_Area;
	int m_RequiredDirection;
	bool m_Active;
};

extern list<InteractZone*> g_interactZones;
