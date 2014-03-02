#ifndef environment_h
#define environment_h

#include "entity.h"

class Environment :
	public Entity
{
public:
	Environment(int x, int y);
	~Environment(void);

	void update();
	void render();

private:
	static int const square_size = 32;
	SDL_Surface* entire_image; //The culmination of the total image made by the code in the constructor.
	SDL_Rect* sprites[ 8 ][ 5 ]; //All of the clip positions
	void set_skin() { skin = NULL; };
};

#endif