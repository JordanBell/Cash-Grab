#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"

#pragma once
class Entity
{
public:
	float x, y;

	//Constructors
	Entity(int x, int y) : cycle(0), x(x), y(y), skin(nullptr), m_renderPriority(0) { }
	virtual ~Entity(void)
    {
        //SDL_FreeSurface(sprite_sheet); // Doing this might delete the sprite_sheet while it is being used by other entities
        
        // Skin deletion should be managed by subclasses
    }

	virtual void update(int delta) = 0;
	virtual void render();
	SDL_Rect GetCenter();
	const int GetRenderPriority(void) const { return m_renderPriority; }

protected:
	int delay; //The Delay before cycling through each sprite. Make smaller to speed up the animation
	int cycle;
	int max_cycles;
	int m_renderPriority;
	SDL_Rect* skin;
	SDL_Surface* sprite_sheet;
	
	virtual void set_skin() { skin = nullptr; }
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }
};

#endif