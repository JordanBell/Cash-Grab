#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"

#pragma once
class Entity
{
public:
	int x, y;

	//Constructors
	Entity(int x, int y) : cycle(0), x(x), y(y) { }
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }

	static void set_sheet(SDL_Surface* sheet) { sprite_sheet = sheet; };

	virtual void update() = 0;
	void render();

protected:
	int delay; //The Delay before cycling through each sprite. Make smaller to speed up the animation
	int cycle;
	int max_cycles;
	SDL_Rect* skin;
	static SDL_Surface* sprite_sheet;
	
	virtual void set_skin() = 0;
	void inc_cycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; };
};

#endif