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
	Entity(int x, int y) : cycle(0), x(x), y(y) { }
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }

	virtual void update(int delta) = 0;
	virtual void render();

protected:
	int delay; //The Delay before cycling through each sprite. Make smaller to speed up the animation
	int cycle;
	int max_cycles;
	SDL_Rect* skin;
	SDL_Surface* sprite_sheet;
	
	virtual void set_skin() = 0;
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }
};

#endif