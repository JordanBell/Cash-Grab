#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "entity.h"

class Coin : public Entity
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y) : sx(start_x), sy(start_y), ex(end_x), ey(end_y) { Coin(); }
	Coin(void);
	~Coin(void);

	void update();

protected:
	SDL_Rect* sprites[ 8 ]; //The 8 sprite locations in the sprite sheet
	void set_skin() { skin = sprites[cycle]; };

private:
	static int const square_size = 32;
	int sx, sy, ex, ey;
};


#endif

