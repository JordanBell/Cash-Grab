#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "entity.h"
class Coin : public Entity
{
public:
	Coin(void);
	~Coin(void);

	void update();

protected:
	SDL_Rect* sprites[ 8 ]; //The 8 sprite locations in the sprite sheet
	void set_skin() { skin = sprites[cycle]; };

private:
	static int const square_size = 32;
};

#endif

