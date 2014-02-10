#pragma once
#include "entity.h"
class Coin :
	public Entity
{
public:
	Coin(void);
	~Coin(void);

	void update();
	void render();

protected:
	SDL_Rect* sprites[ 8 ]; //The 8 sprite locations in the sprite sheet

	void set_skin();
};

