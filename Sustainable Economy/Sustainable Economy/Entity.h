#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"

class Entity
{
public:
	int x, y;

	Entity(void);
	Entity(SDL_Surface* sheet) : sprite_sheet(sheet), cycle(0) { }
	~Entity(void);

	virtual void update() = 0;
	virtual void render() = 0;

protected:
	int delay;
	int cycle;
	SDL_Rect* skin;
	SDL_Surface* sprite_sheet;
	
	virtual void set_skin() = 0;
	void incCycle(void);
};

#endif